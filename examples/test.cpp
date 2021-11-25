//
// Created by Chuang Yao on 10/21/2021.
//

#include "ht/DataHandler/all.hpp"
#include "ht/Event/all.hpp"
#include "ht/HackTest.hpp"

// WARNING: std::filesystem might not work on some versions of macOS!
namespace fs = std::filesystem;

int main() {
  HackTest::say_hello();

  // creating an event queue
  HackTest::EventQueue q;

  // testing manually constructing events and adding them to the event queue;
  // in the finished library, these should be automatically generated by
  // different Handlers
  HackTest::MarketEvent me(q);
  HackTest::SignalEvent se(q, "AAPL", "LONG");
  HackTest::OrderEvent oe(q, "AAPL", "MKT", 100, "SHORT");
  HackTest::FillEvent fe(q, "AAPL", "NASDAQ", 100, "LONG", 0.02);
  q.show();

  // path to the directory containing csv price files
  // please manually modify this if you want to run it on your computer
#ifdef __linux__
  fs::path path{"/home/chuang/HackTest/examples/data"};
#endif
#ifdef _WIN32
  fs::path path{R"(C:\Users\Chuang\CLionProjects\HackTest\examples\data)"};
#endif
#ifdef __APPLE__
  fs::path path{"/Users/cyao/Developer/CLionProjects/HackTest/examples/data"};
#endif

  // a list of symbols with existing csv data files
  std::vector<std::string> symbols{"AAPL", "^IXIC", "MSFT"};
  HackTest::HistoricalCsvHandler dh(q, path, symbols);

  // no data on AMD, should output "No data ..."
  dh.show_data_on_date("AMD", "2019-06-13");

  // test if csv file is properly read
  dh.show_data_on_date("AAPL", "2019-06-13");
  dh.show_data_on_date("AAPL", "2021-06-13");
  dh.show_data_on_date("MSFT", "2019-06-13");
  dh.show_data_on_date("MSFT", "2021-06-13");

  // test if the member function is working
  dh.get_latest_bars("AAPL", 5);
  dh.get_latest_bars("MSFT", 5);
}
