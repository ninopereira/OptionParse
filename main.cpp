#include <iostream>
#include "option_parser.h"
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
  //Create parsing options
  op::OptionParser opt;
  opt.add_option("-h", "--help", "show option help");
  opt.add_option("-i1","--input_1","first number (REQUIRED)","2.0");
  opt.add_option("-i2","--input_2","second number (REQUIRED)","3.0");
  opt.add_option("-sum","--summation","Sum operation (ONE OF REQUIRED VARIANT)");
  opt.add_option("-sub","--subtraction","Sum operation (ONE OF REQUIRED VARIANT)");
  opt.add_option("-v","--verbose","Verbosity trigger");
  opt.add_option("-o","--output","Path to the output directory (REQUIRED)","");
  opt.add_option("-n","--name","Name of the output file","output");

  //Parsing options
  bool correctParsing = opt.parse_options(argc, argv);
  if(!correctParsing)
    return EXIT_FAILURE;

  //Parameters

  //We can read integers
  // const int number1 = op::str2int(opt["-i1"]);
  // const int number2 = op::str2int(opt["-i2"]);
  
  //Or doubles
  const double number1 = op::str2double(opt["-i1"]);
  const double number2 = op::str2double(opt["-i2"]);
  
  const bool verbose = op::str2bool(opt["-v"]);
  const bool hasHelp = op::str2bool(opt["-h"]);

  const bool isSum = op::str2bool(opt["-sum"]);
  const bool isSub = op::str2bool(opt["-sub"]);

  std::string output_path = opt["-o"];

  //Making checks
  if(hasHelp) 
  {
    opt.show_help();
    return 0;
  }

  if(output_path == "")
  {
    cerr << "Please specify the path of the output directory." << endl;
    opt.show_help();
    return EXIT_FAILURE;
  }

  if(output_path[output_path.size()-1] != '/')
  {
    output_path.append("/");
  }

  string output_iter_path = output_path + opt["-n"] + ".txt"; 

  if(isSum && isSub)
  {
    cerr << "Please choose only one operation !" << endl;
    opt.show_help();
    return EXIT_FAILURE;
  }

  
  if(isSum)
  {
	std::cout << "Result: " << number1 + number2 << std::endl;
  }
  else if (isSub)
  {
	std::cout << "Result: " << number1 - number2 << std::endl;
  }
  else
  {
    cerr << "Please choose at least one operation (summation or subtraction)." << endl;
    opt.show_help();
    return EXIT_FAILURE;
  }
  return 0;
}
