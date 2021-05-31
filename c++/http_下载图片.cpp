void httpact()
{
	auto http_req = [=]() {
		//std::string uri = "https://logoimg.deyioo.com/teams/20190219230655629_100x100.png";
		std::string uri = "127.0.0.1:8081";
		std::string spath = "/100x100.png";
		
		bsoncxx::builder::basic::document builder{};
		auto bsonobj = builder.view();
		std::string params = bsoncxx::to_json(bsonobj);

		auto cb = [=](bool result, std::string info) {
			SLOG_CRITICAL << "yabo get_vlist http_req result[" << result << "] ";
			if (!result)
			{
				SLOG_ERROR << "yabo get_vlist http_req result[" << result << "] " << " path:" << spath << ",uri:" << uri;
				return;
			}

			bsoncxx::stdx::optional<bsoncxx::document::value> value;
			int res = err_code::res_ok;
			if (!result)
			{
				res = err_code::err_http_err_code;
			}
			else
			{
				std::string filename = "./xx.png";
				std::fstream* img = new std::fstream();
				img->open(filename.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::app);
				if (!img->is_open())
				{
					SLOG_ERROR << "File[" << filename << "] can't open:" << filename;
					return;
				}
				img->write(info.c_str(), info.size());
				img->close();
			}

		};
		game_http::create(uri, spath, params, "GET", cb);
	};

	http_req();
}
