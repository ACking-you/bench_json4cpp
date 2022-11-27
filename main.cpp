#include "time.hpp"
#include <iostream>
#include <fstream>
using namespace std;
#include "nlohmann/json.hpp"
using json_nl = nlohmann::json;

#include "Json.h"
using namespace yazi::json;

#include "my-json/Parser.h"
using my_parser = json::Parser;


//输出到valid.json文件方便查看验证是否解析正确
void outPutValidJson(std::string const& src){
  auto ofs = ofstream("../valid.json");
  ofs<<src;
}

//获取用于测试的json数据
std::string getSourceString(){
  auto ifs = ifstream("../test.json");
  if(ifs){
    return string{istreambuf_iterator<char>(ifs),istreambuf_iterator<char>()};
  }
  return {};
}

//测试yaziJson的表现
void testYaziJson()
{
  //get src string
  auto data = getSourceString();
  Json json;
  //start bench
  {
    Timer t;
    json.parse(data);
  }
  //valid string
  outPutValidJson(json.str());
}

//测试nlohmannJson的表现
void testNlohmannJson()
{
   //get src string
  auto data = getSourceString();
  json_nl j;
  //start bench
  {
    Timer t;
    j = std::move(json_nl::parse(data));
  }
  //valid string
  outPutValidJson(j.dump());
}

//测试我的json解析库的表现
void testMyJson(){
    //get src string
  auto data = getSourceString();
  json::JObject j;
  //start bench
  {
    Timer t;
    j = std::move(my_parser::FromString(data));
  }
  //valid string
  outPutValidJson(j.to_string());
}

int main()
{
  for(int i=0;i<10;i++){
    testYaziJson();
    testMyJson();
    testNlohmannJson();
  }
}