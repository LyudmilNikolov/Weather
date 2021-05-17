#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"

map<utility::string_t, utility::string_t> dictionary;

void display_json(
	json::value const& jvalue,
	utility::string_t const& prefix)
{
	wcout << prefix << jvalue.serialize() << endl;
}

void handle_request(
	http_request request,
	function<void(json::value const&, json::value&)> action)
{
	auto answer = json::value::object();

	
	request
		.extract_json()
		.then([&answer, &action](pplx::task<json::value> task) {
		try
		{
			auto const& jvalue = task.get();
			display_json(jvalue, L"R: ");

			if (!jvalue.is_null())
			{
				action(jvalue, answer);
			}
		}
		catch (http_exception const& e)
		{
			wcout << e.what() << endl;
		}
			})
		.wait();


			display_json(answer, L"S: ");

			request.reply(status_codes::OK, answer);
}



void handle_post(http_request request)
{
	TRACE("\nhandle POST\n");

	handle_request(
		request,
		[](json::value const& jvalue, json::value& answer)
		{
		
			for (auto const& e : jvalue.as_object())
			{
				if (e.second.is_string())
				{
					auto key = e.first;
					auto value = e.second.as_string();
					
							if (key == L"day") {
								if (value == L"0") {
									answer[L"city"] = json::value::string(L"Sofia");
									answer[L"temperature"] = json::value::string(L"22.5");
									answer[L"precipitation"] = json::value::string(L"15");
									answer[L"humidity"] = json::value::string(L"20");
								}
								if (value == L"1") {
									answer[L"city"] = json::value::string(L"Sofia");
									answer[L"temperature"] = json::value::string(L"20.5");
									answer[L"precipitation"] = json::value::string(L"10");
									answer[L"humidity"] = json::value::string(L"10");
								}
								if (value == L"2") {
									answer[L"city"] = json::value::string(L"Sofia");
									answer[L"temperature"] = json::value::string(L"10");
									answer[L"precipitation"] = json::value::string(L"40");
									answer[L"humidity"] = json::value::string(L"40");
								}
					}
					

					if (dictionary.find(key) == dictionary.end())
					{
						TRACE_ACTION(L"added", key, value);
						answer[key] = json::value::string(L"<put>");
					}
					else
					{
						TRACE_ACTION(L"updated", key, value);
						answer[key] = json::value::string(L"<updated>");
					}

					dictionary[key] = value;
				}
			}
		});
}



int main()
{
	http_listener listener(L"http://localhost:12345"); 

	
	listener.support(methods::POST, handle_post);
	

	try
	{
		listener
			.open()
			.then([&listener]() {TRACE(L"\nstarting to listen\n"); })
			.wait();

		while (true);
	}
	catch (exception const& e)
	{
		wcout << e.what() << endl;
	}

	return 0;
}
