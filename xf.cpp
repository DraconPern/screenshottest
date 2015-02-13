
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp> 

#include "firefoxcontrol.h"

using namespace std;

int searchreplacefile(string filename, string search, string replace)
{
	std::ifstream ifs(filename.c_str());  
	string allcontent((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();
	
	boost::replace_all(allcontent, search, replace);
	
	std::ofstream ofs(filename.c_str());  
	ofs << allcontent;
	ofs.close();

	return 0;
}

int fixpagesaver()
{
	searchreplacefile("/root/{c151d79e-e61b-4a90-a887-5a46d38fba99}/chrome.manifest", "jar:chrome/pagesaver.jar!", "chrome");
	searchreplacefile("/root/{c151d79e-e61b-4a90-a887-5a46d38fba99}/chrome/content/browserOverlay.js", "!failedToWritePrefs", "false");
	
	return 0;
}

int createfirefoxpref()
{
	std::ofstream localsettings("/usr/lib64/firefox/browser/defaults/preferences/local-settings.js");
	localsettings << "pref(\"general.config.obscure_value\", 0);" << endl;
	localsettings << "pref(\"general.config.filename\", \"mozilla.cfg\");" << endl;	
	localsettings.close();
	
	std::ofstream mozillacfg("/usr/lib64/firefox/mozilla.cfg");
	mozillacfg << "//" << endl;
	mozillacfg << "lockPref(\"browser.startup.homepage\", \"about:blank\");" << endl;
	mozillacfg << "lockPref(\"pagesaver.file.saveDir\", \"~/\");" << endl;
	mozillacfg << "lockPref(\"pagesaver.file.name\", \"%u\");" << endl;
	mozillacfg << "lockPref(\"pagesaver.file.overwrite\", true);" << endl;
	mozillacfg << "lockPref(\"pagesaver.file.prompt\", false);" << endl;
	mozillacfg << "lockPref(\"pagesaver.flash.arrangeToCapture\", true);" << endl;
	mozillacfg << "lockPref(\"pagesaver.captureportion\", 1);" << endl;
	mozillacfg << "lockPref(\"pagesaver.image.format\", \"image/png\");" << endl;
	mozillacfg.close();
	return 0;
}

int launchXWindows(int screennumber)
{
	stringbuf buf;
	ostream o(&buf);
	o << "Xvfb :" << screennumber << " -ac -screen 0 1600x1200x24+32 &";
	system(buf.str().c_str());
	return 0;
}

int createfirefoxprofile(int screennumber)
{
	stringbuf buf;
	ostream o(&buf);
	o << "export DISPLAY=:" << screennumber << ".0 ; firefox -createprofile " << screennumber;
	system(buf.str().c_str());	
}

int screenshot(int screennumber, string url)
{
	stringbuf buf;
	ostream o(&buf);
	o << "export DISPLAY=:" << screennumber << ".0 ; firefox -no-remote -P " << screennumber << " -captureflash -width 1048 -height 1189 -savedelay 1000 -saveimage " << url;
	system(buf.str().c_str());	
}

int installsystem()
{
	system("yum install wget unzip firefox Xvfb -y");	
	system("yum install ipa-mincho-fonts ipa-pmincho-fonts ipa-gothic-fonts ipa-pgothic-fonts vlgothic-fonts vlgothic-p-fonts -y");
	system("unzip -o ~/pagesaverbasic-2.8.2.xpi -d ~/{c151d79e-e61b-4a90-a887-5a46d38fba99}");
	
	fixpagesaver();

        system("rm -rf ~/.mozilla");	
	createfirefoxpref();
	
	system("rm -rf /usr/lib64/firefox/browser/extensions/{c151d79e-e61b-4a90-a887-5a46d38fba99}");
	system("mv ~/{c151d79e-e61b-4a90-a887-5a46d38fba99} /usr/lib64/firefox/browser/extensions/");
	
	return 1;
}

int main(int argc, char *argv[])
{
  try
  {

      firefoxcontrol x;
	  // std::cout << x.getprofilepath("1f01");
	  
	  if(!installsystem())
	  {
		std::cout << "FAIL\n";
		return 0;
      }		
	  	  
	  launchXWindows(100);
          sleep(1000);
          launchXWindows(200);
          sleep(1000);
	  createfirefoxprofile(100);
	  createfirefoxprofile(200);

	  screenshot(100, "http://www.animegao.com");
	  screenshot(200, "http://www.cnn.com");
	  
	  cout << "Done!\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }
  return 1;
}
