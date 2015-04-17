/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file myshmclient.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Robocar City Emulator and Robocar World Championship
 *
 * desc
 *
 */

#include <myshmclient.hpp>
//#include <trafficlexer.hpp>
#define DIST 2000
char data[524288];

void
justine::sampleclient::MyShmClient::car (boost::asio::ip::tcp::socket & socket, int id, unsigned *f,unsigned *t, unsigned *s)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<car ");
  length += std::sprintf (data + length, "%d>", id);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  int
    idd
  {
  0};
  std::sscanf (data, "<OK %d %u %u %u", &idd, f, t, s);

  //std::cout.write ( data, length );
  //std::cout << "Command CAR sent." << std::endl;

}

//mégis csak írunk egy függvény ami szépen visszaadja majd nekünk azt hogy a gengszterek egymáshoz képest milyen messze helyeszkednek el itt is szépen berendezzük melyik gengszterhez hányan vannak a legközelebb
//igazából ez csak prototípusként lényeges, lehetséges hogy nem is haszáljuk majd csak a működése végett vagyunk kíváncsiak hogy esetleges teljesítménynövekedést érünk-e el vele



justine::sampleclient::MyShmClient::Gangster justine::sampleclient::MyShmClient::gengitavok (boost::asio::ip::tcp::socket & socket)
{

  boost::system::error_code err;

  /*size_t length = std::sprintf (data, "<gangsters ");
  length += std::sprintf (data + length, "%d>", id);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }
*/
  //lényeg :D


  /* reading all gangsters into a vector */
  int idd{0};
  unsigned f,t,s;
  unsigned int g;
  int n{0};
  int nn{0};
  //gengi vektor
  std::vector < Gangster > gangsters;
  //ugyanúgy beaddoljuk a gengiket egy vektorba
  while (std:: sscanf (data + nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n) == 4) //
    {
      nn += n;
      gangsters.push_back (Gangster{idd, f, t, (int)s});
    }
  
  //rendezzük őket nem egy rendőrhöz képest hanem egymáshoz :O
  //tehát mindig kiválasztunk egy gengit és 
  
  Gangster gl,rg;
  int max = 0;
  for(auto it = gangsters.begin(); it != gangsters.end(); it++)
  {      
	gl = *it;
	gl.neargang = 0;
	
  	for(int i = 0; i < (int)gangsters.size(); i++)
  	{
  		g = gangsters[i].to;
  		if( dst(gl.to,g) < 2000)
  		{
  			gl.neargang++;
  		}
  	}
  	if(gl.neargang > max)
  	{
  		max = gl.neargang;
  		rg = gl;
  	}
 
  }
 /* std::sort (gangsters.begin (), gangsters.end (),[] (Gangster x, Gangster y)
  {
     return x.neargang > y.neargang;
    
  }
  );*/
  
  //g = gangsters[0];
  
  
  //auto *it = gangsters.begin();
  
 
  //std::cout << "Legtöbb gengis:"<< gl.id << " G sz:" << gl.neargang << std::endl;
  //std::cout.write ( data, length );
  //std::cout << "Command GANGSTER sent." << std::endl;
  //std::cout.write ( data, length );
 // std::cout << "Command GENGI sent." << std::endl;
  return rg;
  
}



std::vector < justine::sampleclient::MyShmClient::Gangster >
  justine::sampleclient::MyShmClient::gangsters (boost::asio::ip::tcp::
						 socket & socket, int id,
						 osmium::
						 unsigned_object_id_type cop)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<gangsters ");
  length += std::sprintf (data + length, "%d>", id);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  /* reading all gangsters into a vector */
  int idd{0};
  unsigned f,t;
  int s;
  int n{0};
  int nn{0};
  std::vector < Gangster > gangsters;

  while (std::sscanf (data + nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n) == 4) //
    {
      nn += n;
      gangsters.push_back (Gangster{idd, f, t, s});
    }
   
 std::sort (gangsters.begin (), gangsters.end (),
	     [this, cop] (Gangster x, Gangster y)
	     {
	     return dst (cop, x.to) < dst (cop, y.to);}
  );
  
  //std::cout.write ( data, length );
  //std::cout << "Command GANGSTER sent." << std::endl;

  return gangsters;
}

std::vector < justine::sampleclient::MyShmClient::Cop >
  justine::sampleclient::MyShmClient::initcops (boost::asio::ip::tcp::
						socket & socket)
{

  boost::system::error_code err;

  size_t
    length =
    std::sprintf (data, "<init guided %s 10 c>", m_teamname.c_str ());

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);


  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);
    }

  /* reading all gangsters into a vector */
  int idd{0};
  int f,t;
  char c;
  int n{0};
  int nn{0};
  std::vector < Cop > cops;

  while (std::
	 sscanf (data + nn, "<OK %d %d/%d %c>%n", &idd, &f, &t, &c, &n) == 4)
    {
      nn += n;
      cops.push_back (idd);
    }

 // std::cout.write (data, length);
  //std::cout << "Command INIT sent." << std::endl;

  return cops;
}


int
justine::sampleclient::MyShmClient::init (boost::asio::ip::tcp::socket & socket)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<init guided %s 1 c>", m_teamname.c_str ());

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  int
    id
  {
  0};
  std::sscanf (data, "<OK %d", &id);

  //std::cout.write (data, length);
  //std::cout << "Command INIT sent." << std::endl;

  return id;

}

void
justine::sampleclient::MyShmClient::pos (boost::asio::ip::tcp::
					 socket & socket, int id)
{

  boost::system::error_code err;

  size_t
    length = std::sprintf (data, "<pos ");
  length +=
    std::sprintf (data + length, "%d %u %u>", id, 2969934868u, 651365957u);

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  //std::cout.write (data, length);
  //std::cout << "Command POS sent." << std::endl;
}



void
justine::sampleclient::MyShmClient::route (boost::asio::ip::tcp::socket & socket, int id,std::vector <osmium::unsigned_object_id_type >&path){

  boost::system::error_code err;

  size_t length = std::sprintf (data,"<route %lu %d", path.size (), id);

  for (auto ui:path){

  	length += std::sprintf (data + length, " %lu", ui);
  }

  length += std::sprintf (data + length, ">");

  socket.send (boost::asio::buffer (data, length));

  length = socket.read_some (boost::asio::buffer (data), err);

  if (err == boost::asio::error::eof)
    {

      // TODO

    }
  else if (err)
    {

      throw
      boost::system::system_error (err);

    }

  //std::cout.write (data, length);
  //std::cout << "Command ROUTE sent." << std::endl;

}

void
justine::sampleclient::MyShmClient::start (boost::asio::io_service & io_service,const char *port)
{

#ifdef DEBUG
  foo ();
#endif

  boost::asio::ip::tcp::resolver resolver (io_service);
  boost::asio::ip::tcp::resolver::query query (boost::asio::ip::tcp::v4 (),"localhost", port);
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve (query);

  boost::asio::ip::tcp::socket socket (io_service);
  boost::asio::connect (socket, iterator);

  int id = init (socket);

  pos (socket, id);

  unsigned int
    g{0u}, gg{0u}, f{0u}, t{0u}, s{0u};

  car (socket, id, &f, &t, &s);
  //gangstereket egy vectorba menjtük
  std::vector < Gangster > gngstrs;
  std::vector < Gangster >::iterator it;
  int GC = 0;
  justine::sampleclient::MyShmClient::Gangster MG;
  //végtelen ciklussal "futtatjuk" az algoritmusunkat
  for (;;)
    {
    	
      std::this_thread::sleep_for (std::chrono::milliseconds (200));
	  MG = gengitavok(socket);
      car (socket, id, &f, &t, &s);
      
      gngstrs = gangsters (socket, id, t);

      if (gngstrs.size () > 0){

			g = gngstrs[0].to;
	  }

	  else{

			g = 0;
	  }

      if (g > 0){

		  //std::cout << "\n";
		  //gatlag /= i;
		  //sleep (1);
		  //std::cout << "A:" << gatlag << "\n";
		  GC = 0;
		  for(int i = 0; i < (int)gngstrs.size(); i++){

		    gg = gngstrs[i].to;
		    if(dst(t,gg) < DIST){

		      	GC++;

		    }
		  }
	  
	  std::cout<< DIST <<"egységnyi távolságon belüli gengszterek száma:" << GC <<std::endl;
	  std::vector <osmium::unsigned_object_id_type> pathG = hasDijkstraPath(t,MG.to);
	  std::vector < osmium::unsigned_object_id_type > path = hasDijkstraPath (t, g);
      std::cout << "Legtöbb gengis és a rendőrbácsi távolsága:" << dst(t,MG.to) << " gengijei:"<< MG.neargang <<std::endl;

	  if (path.size () > 1){

		 if(dst(t,MG.to) < DIST*2){

		      //std::copy ( path.begin(), path.end(),
		      //          std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );
				std::cout << "Legközelebbi gengit kergetem!" << std::endl;
		      route (socket, id, path);
		     }

	     else{

	     	std::cout << "legtöbb gengishez megyek! - " << MG.to << " gengijei:"<< MG.neargang <<std::endl;
	     	route(socket,id,pathG);
	     }

	    }
	}
  }
}

void
justine::sampleclient::MyShmClient::start10 (boost::asio::io_service & io_service,const char *port)
{
#ifdef DEBUG
  foo ();
#endif

  boost::asio::ip::tcp::resolver resolver (io_service);
  boost::asio::ip::tcp::resolver::query query (boost::asio::ip::tcp::v4 (),"localhost", port);
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve (query);

  boost::asio::ip::tcp::socket socket (io_service);
  boost::asio::connect (socket, iterator);

  std::vector < Cop > cops = initcops (socket);

  unsigned int g{0u}, gg{0u}, f{0u}, t{0u}, s{0u}, ct{0u};
 
  unsigned int ds = 2000;

  std::vector < Gangster > gngstrs,gtavok;
  int p = 0;
  
  //int CopOk[10] = {0,0,0,1,1,1,1,1,1,1};
  //int Help [10] = {0};
  //védéshez kellett...
  //unsigned int  MGC = 2000;
  //bool isMade = false;
  //GD a distancehez kell ebben tároljuk el milyen ...
  //unsigned int GD[11] = {0};
  //GP lesz a gengszterek száma rendőrönként
  unsigned int GP[11] = {0};
  unsigned int CTC[10];
  unsigned int MGP {0u};
  unsigned int BCOP = 0;
  unsigned int BCOPR[10] = {0};
  justine::sampleclient::MyShmClient::Gangster MG;

  /*------------------------------------------------------------------------------------------------------------------------------------------------------*/
  //v.0.1
  //Rádius keresés - mérték egyenlőre állandó vagy dinamikusan az aktuális helyzetekhez kialakított
  //Gengszterek számának meghatározása "területenként", az aktuális egységnyi sugarú "körön" belül
  //Akinél nincs gengszter elindul a legközelebb lévő rendőrhöz hogy segítsen neki.
  //Menet közben ha talál gengsztert és az legalább a fele mint amelyik rendőrhöz indul akkor üldözés üzemmódba vált.
  //Ha egy rendőr kerületében több mint X (egyenlőre ez a szám legyen 6-7-8) akkor segítséget hív és a legközelebbi tétlet rendőrt magához rendeli
  //a nagyobb gengszterfogás érdekében

  /*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //TODO:
  //távolságok lekérése - vektorban való tárolás (nekem ez most tömb lesz v.0.1)
  //ezzel együtt mindig a legnagyobb gengszterrel rendelkező rendőr eltárolása - NODE ID (mindig t változó lesz)
  //tevékenység vektor - alapból mindenki járőrözik
  //segítség vektor - lényegében egy bitvektor ami ha úgy gondolja az algoritmusunk akkor átállítja 1-re az aktuális rendőrét és ezzel kiküldve a jelet a többi társnak
  //egyenlőre semmiféle újabb függvényt nem írunk csak egyszerűen az alap működést próbáljuk belőni majd a lentebb levő végtelen ciklusban :)
  //két rendőr ne menjen ugyan arra a node-ra, ezt tömb segítségével....
  //mindig lesz egy kitüntetett rendőr aki a legtöbb gengivel rendelkezik.
  //kíváncsi vagyok az eredményre
  //2015 04 16
  /*---------------------------------------------------------------------------------------------------------------------------------------------------*/

  //Debrecen5 - re el kell hogy készüljön! szeretnénk élesben is tesztelni!
  for (;;)
    {

    std::this_thread::sleep_for (std::chrono::milliseconds (200));
    //A p lesz nekünk mindig az aktuális index, szükségszerűen most itt nullázik ki.
    p = 0;
    //isMade = false;
    MGP = 0;
    //BCOPR[p] = 0;
  	MG = gengitavok(socket);
	std::cout << "-------------------------------------------------------------"<< std::endl;
	//for ciklussal fogjuk bejárni a cop vektorunkat, ebben a verzióban én most lecseréltem az auto cop:cops -os bejárást, jelenelg nekem az iterátoros megoldás jobban tetszik :)
	//előbb számolunk körzetet hogy ne gabajodjanak össze a rendőrök.
	
	for(auto it = cops.begin(); it != cops.end(); it++)
	{
		GP[p] = 0;
		car (socket, *it, &f, &t, &s);
		//gtavok = gengitavok(socket,*it);
		 for(int i = 0; i < (int)gngstrs.size(); i++){
		  gngstrs = gangsters (socket, *it, t);
			gg = gngstrs[i].to;	
			      if(dst(t,gg) < DIST){
				  GP[p]++;		  
				}
		  }
		  if(GP[p] > MGP){
		      		BCOP = t;
		      		MGP = GP[p];
		      		//if(ismade == false)
		      		//{
		      			std::cout << "Maxgengi:" << MGP <<  std::endl;
		      		//}
		      }
		     p++;
	}
	p = 0;

	//for ciklussal fogjuk bejárni a cop vektorunkat, ebben a verzióban én most lecseréltem az auto cop:cops -os bejárást, jelenelg nekem az iterátoros megoldás jobban tetszik :)
    for (auto it = cops.begin(); it != cops.end(); it++)
	{
		
	//if(p!= 10) p++;

	//car függvény meghívása, f- honnan ,t - hova, s - hanyadik lépésnél járhat (tipp)
	  car (socket, *it, &f, &t, &s);
	  CTC[p] = t;
	  
	 
	//std::cout << "Rendor:" << *it << " Honnan:" << f << " Hova:" << t << " Lépés:" << s << std::endl;
	 

 	//1. robocaros védési feladat... itt hagyjuk hátha még jó lesz :)
	///if(isMade == false && p == 0)
	//{
		  gngstrs = gangsters (socket, *it, t);

	//  isMade = true;
	//  }

	  

	//Megnézzük hogy a gengszter vektorunk üres -e vagy sem. (van e éppen gengszter felcsatolva vagy sem?!)
	  if (gngstrs.size () > 0)
	    {
	//mivel a gangster függvényünk szépen rendezte a vektorunk ezért a 0. elem mindig az aktuális rendőrhöz legközelebb eső gengsztert adja vissza
	      g = gngstrs[0].to;
	//gl = gngstrs[gngstrs.size () - 1].to;
	    }

	  else
	    {
	    //ha nincs gengi akkor legyen 0
	      g = 0;
	    }
	    
	  //össze szeretném gyűjteni a rendőrök X egységnyi sugarán belüli gengsztereket,
	  //és ezek alapján eldönteni hogy melyik "területen" érdemes a gengsztereket üldözni
	  //ha van gengink akkor szépen lőjük az algoritmust

	  if (g > 0)
	    {

	    	//Legelső dolgunk a távok felmérése és a "körön" belüli gengszterek eltárolása.

	      //GC[p] = dst(t,g);
	     // std::cout<<"Táv:" << GC[p+1] <<std::endl;
	      //GP[p] = g;

	    /* for(int i = 0; i < gngstrs.size(); i++)
	      {
	       		gg = gngstrs[i].to;	

				if(dst(t,gg) < ds)
				{
				  GP[p]++;		  
				}	

	      }*/
	      auto itc = cops.begin();
	      //itt megnézzük hogy milyen közel van az esetleges kitüntetett rendőrünkhöz
	      for(int i = 0;  i < p; i++, itc++)
	      {
		      car (socket, *it, &f, &ct, &s);
	       		//gg = gngstrs[i].to;	
	      		if(i != p)
	      		{
					if(dst(t,ct) < ds/2 && BCOPR[i] == 0)
					{
					 	BCOPR[i] = 0;  
					}
				}	

	      }

	      std::cout << p << ". rendor körzetében " << GP[p] << "gengi..." << std::endl;

	      	/* if(GP[p] > MGP)
		      {
		      		BCOP = t;
		      		MGP = GP[p];
		      		//if(ismade == false)
		      		//{
		      			std::cout << "Maxgengi:" << MGP <<  std::endl;
		      		//}
		      }*/
		 //ha nulla a gengszterszám akkor elindulunk a legnagyobb gengivel rendelkező zsaru felé
		 //ha 0 vagy a fele kisebb mint a legnagyobb számú rendőré és nem csinál semmit vagy ha a táv kisebb mint X hogyha van a közelében gengi

		 if(GP[p] == 0 || ((GP[p]/2 < MGP) && BCOPR[p] == 0))
		 {
		 	std::vector<osmium::unsigned_object_id_type> nogpath = hasDijkstraPath ( t, BCOP );
		 	std::cout << p << ". rendor elindult a kitüntetett rendőr irányába." << std::endl;
		 	BCOPR[p] = 1;
		 	route(socket,*it,nogpath);
		 }

		else if(BCOPR[p] == 1 && dst(t,BCOP) < 100)
		{
			g = gngstrs[0].to;
			std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );
		      if (path.size () > 1)
				{
				 route (socket, *it, path);
				}
		}
		 else
		 	{
		 		for(int i = 0; i < p; i++)
		 		{
		 			if(i != p)
		 			{
		 				if(CTC[i] == CTC[p])
		 				{
		 					g = gngstrs[0].to;
		 				}
		 			}
		 		}

		 		std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );
		 		std::vector<osmium::unsigned_object_id_type> pathg = hasDijkstraPath ( g, t );
		 		if(path == pathg)
		 			std::cout << "zsaru és gengszter útvonala megegyezik" << std::endl;
		      if (path.size () > 1)
				{
				 route (socket, *it, path);
				}
		}
	      //az összes gengszter 
		//std::cout << "p:" << p << std::endl;
				/*if(p == 10)
		{	

			
	  		if(isMade == false)
	  		{
	  			for(int i = 1; i < p+1; i++)
			{
				    std::cout<<"Táv:" << GC[i] << " Node ID: "<< GP[i] <<std::endl;
			if(GC[i] < MGC)
			      {
					      MGC = GC[i];
					      MGP = GP[i];
					      std::cout<<"Csere - " << i <<std::endl;
			      }
			    }
				    std::cout<<"Legközelebbi táv:" << MGC <<std::endl;
				 
				  std::cout<<"L:" << g <<std::endl;
				  isMade = true;
	  		}
		}*/
	      //std::cout<< p <<".szamu rendor 1000 egységnyi távolságon belüli gengszterek száma:" << GC[p] <<std::endl;
	      
	      //g = MGP;

	     // std::vector<osmium::unsigned_object_id_type> pathl = hasDijkstraPath ( t, l );
	      
		}
	p++;
	}
  }
}


