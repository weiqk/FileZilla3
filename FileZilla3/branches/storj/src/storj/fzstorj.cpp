#include <stdio.h>

#include "events.hpp"

#include <libfilezilla/format.hpp>

#include "storj.h"

template<typename ...Args>
void fzprintf(storjEvent event, Args &&... args)
{
	fputc('0' + static_cast<int>(event), stdout);

	std::string s = fz::sprintf(std::forward<Args>(args)...);
	fwrite(s.c_str(), s.size(), 1, stdout);

	fputc('\n', stdout);
	fflush(stdout);
}

bool getLine(std::string & line)
{
	line.clear();
	while (true) {
		int c = fgetc(stdin);
		if (c == -1) {
			return false;
		}
		else if (!c) {
			return line.empty();
		}
		else if (c == '\n') {
			return !line.empty();
		}
		else if (c == '\r') {
			continue;
		}
		else {
			line += static_cast<unsigned char>(c);
		}
	}
}

namespace {
extern "C" void get_buckets_callback(uv_work_t *work_req, int status)
{
	if (status != 0) {
		fzprintf(storjEvent::Error, "Request failed with outer status code %d", status);
		exit(1);
	}

	json_request_t *req = static_cast<json_request_t *>(work_req->data);

	if (req->status_code != 200) {
		fzprintf(storjEvent::Error, "Request failed with status code %d", req->status_code);
		exit(1);
	}

	if (req->response == NULL) {
		free(req);
		free(work_req);
		fzprintf(storjEvent::Error, "Failed to list buckets for an unknown reason.");
		exit(1);
	}

	int num_buckets = json_object_array_length(req->response);
	struct json_object *bucket{};

	for (int i = 0; i < num_buckets; ++i) {
		bucket = json_object_array_get_idx(req->response, i);

		struct json_object *id_obj{};
		json_object_object_get_ex(bucket, "id", &id_obj);
		struct json_object *name_obj{};
		json_object_object_get_ex(bucket, "name", &name_obj);

		if (id_obj && name_obj) {
			char const* name = json_object_get_string(name_obj);
			char const* id = json_object_get_string(id_obj);
			if (name && *name && id && *id) {
				std::string sname = name;
				std::string sid = id;
				fz::replace_substrings(sname, "\r", "");
				fz::replace_substrings(sid, "\r", "");
				fz::replace_substrings(sname, "\n", "");
				fz::replace_substrings(sid, "\n", "");
				fzprintf(storjEvent::Listentry, "%s\n-1\n%s", sname, sid);
			}
		}
	}

	// Cleanup
	json_object_put(req->response);
	free(req);
	free(work_req);
}

extern "C" void list_files_callback(uv_work_t *work_req, int status)
{
	if (status != 0) {
		fzprintf(storjEvent::Error, "Request failed with outer status code %d", status);
		exit(1);
	}

	json_request_t *req = static_cast<json_request_t *>(work_req->data);

	if (req->status_code != 200) {
		fzprintf(storjEvent::Error, "Request failed with status code %d", req->status_code);
		exit(1);
	}

	if (req->response == NULL) {
		free(req);
		free(work_req);
		fzprintf(storjEvent::Error, "Failed to list buckets for an unknown reason.");
		exit(1);
	}

	int num_files = json_object_array_length(req->response);
	struct json_object *file{};

	for (int i = 0; i < num_files; ++i) {
		file = json_object_array_get_idx(req->response, i);

		struct json_object *id_obj{};
		json_object_object_get_ex(file, "id", &id_obj);
		struct json_object *name_obj{};
		json_object_object_get_ex(file, "filename", &name_obj);
		struct json_object *size_obj{};
		json_object_object_get_ex(file, "size", &size_obj);

		if (id_obj && name_obj && size_obj) {
			char const* name = json_object_get_string(name_obj);
			char const* id = json_object_get_string(id_obj);
			char const* size = json_object_get_string(size_obj);
			if (name && *name && id && *id && size && *size) {
				std::string sname = name;
				std::string sid = id;
				std::string ssize = size;
				fz::replace_substrings(sname, "\r", "");
				fz::replace_substrings(sid, "\r", "");
				fz::replace_substrings(sname, "\n", "");
				fz::replace_substrings(sid, "\n", "");
				fz::replace_substrings(ssize, "\n", "");
				fz::replace_substrings(ssize, "\n", "");
				fzprintf(storjEvent::Listentry, "%s\n%s\n%s", sname, ssize, sid);
			}
		}
	}

	// Cleanup
	json_object_put(req->response);
	free(req);
	free(work_req);
}


extern "C" void download_file_progress(double progress,
								   uint64_t downloaded_bytes,
								   uint64_t total_bytes,
								   void *handle)
{
	fzprintf(storjEvent::Transfer, "%u", downloaded_bytes);
}

extern "C" void download_file_complete(int status, FILE *fd, void *)
{
	if (status) {
		fzprintf(storjEvent::Error, "Download failed with error %s (%d)", storj_strerror(status), status);
	}
	else {
		fzprintf(storjEvent::Done, "1");
	}
}

extern "C" void upload_file_complete(int status, void *)
{
	if (status) {
		fzprintf(storjEvent::Error, "Download failed with error %s (%d)", storj_strerror(status), status);
	}
	else {
		fzprintf(storjEvent::Done, "1");
	}
}

extern "C" void log(char const* msg, int level, void*)
{
	std::string s(msg);
	fz::replace_substrings(s, "\n", " ");
	fz::trim(s);
	fzprintf(storjEvent::Verbose, "%s", s);
}

extern "C" void generic_done(uv_work_t *work_req, int status)
{
	if (status) {
		fzprintf(storjEvent::Error, "Command failed with error %s (%d)", storj_strerror(status), status);
		exit(1);
	}

	json_request_t *req = static_cast<json_request_t *>(work_req->data);

	if (req->status_code != 200) {
		fzprintf(storjEvent::Error, "Request failed with status code %d", req->status_code);
		return;
	}

	fzprintf(storjEvent::Done, "1");
}
}

int main()
{
	fzprintf(storjEvent::Reply, "fzStorj started, protocol_version=%d", FZSTORJ_PROTOCOL_VERSION);

	std::string host;
	unsigned short port = 443;
	std::string user;
	std::string pass;

	storj_env_t *env{};


	auto init_env = [&](){
		if (env) {
			return;
		}
		storj_bridge_options_t options{};
		options.host = host.c_str();
		options.proto = "https";
		options.port = port;
		options.user = user.c_str();
		options.pass = pass.c_str();

		storj_encrypt_options_t encrypt_options{};
		encrypt_options.mnemonic = "";

		storj_http_options_t http_options{};
		http_options.user_agent = "FileZilla";

		static storj_log_options_t log_options{};
		log_options.logger = log;
		log_options.level = 4;
		env = storj_init_env(&options, &encrypt_options, &http_options, &log_options);
	};

	int ret = 0;
	while (true) {
		std::string command;
		if (!getLine(command)) {
			ret = 1;
			break;
		}

		if (command.empty()) {
			break;
		}

		std::size_t pos = command.find(' ');
		std::string arg;
		if (pos != std::string::npos) {
			arg = command.substr(pos + 1);
			command = command.substr(0, pos);
		}

		if (command == "host") {
			host = arg;
			std::size_t sep = host.find(':');
			if (sep != std::string::npos) {
				port = fz::to_integral<unsigned short>(host.substr(pos + 1));
				host = host.substr(0, pos);
			}
			fzprintf(storjEvent::Done, "1");
		}
		else if (command == "user") {
			user = arg;
			fzprintf(storjEvent::Done, "1");
		}
		else if (command == "pass") {
			pass = arg;
			fzprintf(storjEvent::Done, "1");
		}
		else if (command == "list-buckets") {
			init_env();
			assert(env);
			storj_bridge_get_buckets(env, 0, get_buckets_callback);
			if (uv_run(env->loop, UV_RUN_DEFAULT)) {
				fzprintf(storjEvent::Error, "uv_run failed.");
				exit(1);
			}
			fzprintf(storjEvent::Done, "1");
		}
		else if (command == "list") {
			init_env();
			assert(env);
			if (arg.empty()) {
				fzprintf(storjEvent::Error, "No bucket given");
				continue;
			}
			storj_bridge_list_files(env, arg.c_str(), 0, list_files_callback);
			if (uv_run(env->loop, UV_RUN_DEFAULT)) {
				fzprintf(storjEvent::Error, "uv_run failed.");
				exit(1);
			}
			fzprintf(storjEvent::Done, "1");
		}
		else if (command == "get") {
			size_t pos = arg.find(' ');
			if (pos == std::string::npos) {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			std::string bucket = arg.substr(0, pos);
			size_t pos2 = arg.find(' ', pos + 1);
			if (pos == std::string::npos) {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			auto id = arg.substr(pos + 1, pos2 - pos - 1);
			auto file = arg.substr(pos2 + 1);

			if (file.size() >= 3 && file.front() == '"' && file.back() == '"') {
				file = fz::replaced_substrings(file.substr(1, file.size() -2), "\"\"", "\"");
			}

			init_env();
			assert(env);

			FILE *fd = fopen(file.c_str(), "w+");

			if (fd == NULL) {
				int err = errno;
				fzprintf(storjEvent::Error, "Could not open local file %s for writing: %d", file, err);
				continue;
			}

			storj_download_state_t *state = static_cast<storj_download_state_t*>(malloc(sizeof(storj_download_state_t)));

			/*uv_signal_t sig;
			uv_signal_init(env->loop, &sig);
			uv_signal_start(&sig, signal_handler, SIGINT);
			sig.data = state;*/

			// FIXME: C-style casts
			int status = storj_bridge_resolve_file(env, state, bucket.c_str(),
												   id.c_str(), fd, NULL,
												   download_file_progress,
												   download_file_complete);
			if (status) {
				fclose(fd);
				fzprintf(storjEvent::Error, "Could not download file, storj_bridge_resolve_file failed: %d", status);
				continue;
			}
			if (uv_run(env->loop, UV_RUN_DEFAULT)) {
				fclose(fd);
				fzprintf(storjEvent::Error, "uv_run failed.");
				exit(1);
			}
			fclose(fd);
		}
		else if (command == "put") {
			size_t pos = arg.find(' ');
			if (pos == std::string::npos) {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			std::string bucket = arg.substr(0, pos);
			arg = arg.substr(pos + 1);

			if (arg[0] != '"') {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}

			std::string file;
			pos = 1;
			size_t pos2;
			while ((pos2 = arg.find('"', pos)) != std::string::npos && arg[pos2 + 1] == '"') {
				file += arg.substr(pos, pos2 - pos + 1);
				pos = pos2 + 2;
			}
			if (pos2 == std::string::npos || arg[pos2 + 1] != ' ') {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			file += arg.substr(pos, pos2 - pos);
			arg = arg.substr(pos2 + 2);

			if (arg[0] != '"') {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}

			std::string remote_name;
			pos = 1;
			while ((pos2 = arg.find('"', pos)) != std::string::npos && arg[pos2 + 1] == '"') {
				remote_name += arg.substr(pos, pos2 - pos + 1);
				pos = pos2 + 2;
			}
			if (pos2 == std::string::npos || arg[pos2 + 1] != '\0') {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			remote_name += arg.substr(pos, pos2 - pos);


			init_env();
			assert(env);

			FILE *fd = fopen(file.c_str(), "r");

			if (fd == NULL) {
				int err = errno;
				fzprintf(storjEvent::Error, "Could not open local file %s for reading: %d", file, err);
				continue;
			}

			storj_upload_opts_t upload_opts;
			upload_opts.shard_concurrency = 3;
			upload_opts.bucket_id = bucket.c_str();

			upload_opts.file_name = remote_name.c_str();
			upload_opts.fd = fd;

			storj_upload_state_t *state = static_cast<storj_upload_state_t*>(malloc(sizeof(storj_upload_state_t)));

			int status = storj_bridge_store_file(env,
												 state,
												 &upload_opts,
												 nullptr,
												 download_file_progress,
												 upload_file_complete);

			if (status) {
				fzprintf(storjEvent::Error, "Could not upload file, storj_bridge_store_file failed: %d", status);
				continue;
			}
			if (uv_run(env->loop, UV_RUN_DEFAULT)) {
				fzprintf(storjEvent::Error, "uv_run failed.");
				exit(1);
			}
		}
		else if (command == "rm") {

			auto args = fz::strtok(arg, ' ');
			if (args.size() != 2) {
				fzprintf(storjEvent::Error, "Bad arguments");
				continue;
			}
			init_env();
			assert(env);

			int status = storj_bridge_delete_file(env, args[0].c_str(), args[1].c_str(), nullptr, generic_done);

			if (status) {
				fzprintf(storjEvent::Error, "Could not delete file, storj_bridge_delete_file failed: %d", status);
				continue;
			}
			if (uv_run(env->loop, UV_RUN_DEFAULT)) {
				fzprintf(storjEvent::Error, "uv_run failed.");
				exit(1);
			}
		}
		else {
			fzprintf(storjEvent::Error, "No such command: %s", command);
		}

	}

	if (env) {
		storj_destroy_env(env);
	}

	return ret;
}