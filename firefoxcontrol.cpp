

#include "firefoxcontrol.h"


int firefoxcontrol::createprofile(string name)
{
  
  return 0;
}


int firefoxcontrol::deleteprofile(string name)
{

  return 0;
}

string firefoxcontrol::getprofilepath(string name)
{
   std::ifstream ifs("/root/.mozilla/firefox/profiles.ini");
  
  string profileini((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  
  string findline = "Name=" + name;
  int location = profileini.find(findline);
  if(location == -1)
    throw std::runtime_error("can't find profile");
  
  int location2 = profileini.find("Path=", location);
  if(location2 == -1)
    throw std::runtime_error("can't find profile path");
  
  location2 += 5;
  int endofline = profileini.find("\n", location2);
  
  string eh = profileini.substr(location2, endofline - location2);
  
  return eh;  
}