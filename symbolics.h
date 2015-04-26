#pragma once

#include <string>
#include <cmath>

#define PATH_TO_LINHAS "linhas/autocarro/"
#define SUBWAYSTOPSFILE "linhas/metro/linhas"
#define lines { "1","18","22","200","201","202","203","204","205","206","207","208","209","300","301","302","303","304","305","400","401","402","500","501","502","503","504","505","506","507","508","600","601","602","603","604","700","701","702","703","704","705","706","707","800","801","802","803","804","805","806","900","901","902","903","904","905","906","907","1M","3M","4M","5M","7M","8M","9M","10M","11M","12M","13M" }
#define YINICIAL 41.2559
#define YFINAL 41.0942
#define XINICIAL -8.71392
#define XFINAL -8.4637
#define HSIZE 40450
#define VSIZE 62550
#define MARGIN 20
#define DELTAH (XFINAL - XINICIAL)
#define DELTAV (YFINAL - YINICIAL)
#define MAX_DISTANCE 417 // Max walkable distance in meters (equivalent to 5 minutes of walking)
#define LATITUDE_UNIT 110574.28
#define LONGITUDE_UNIT 111302.62
#define DELTAX
#define DELTAY

long double stringToDouble(std::string d);