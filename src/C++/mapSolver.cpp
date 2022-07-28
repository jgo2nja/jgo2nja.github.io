// James O'Connell jgo2nja
// Last Updated 14 July 2022

// map solver program

// pre-processing

#include "city.h"
#include "randGen.h"
#include "pairing_heap.h"
#include <iostream>
#include <string>

// declare city names (source credit: Kingsisle Entertainment Inc. game Wizard101 for names)
const vector<string> wizardCityNames{
				     "Colossus Boulevard, WC", "Cyclops Lane, WC", "Dark Cave, WC", "Firecat Alley, WC", "Golem Court, WC", "Haunted Cave, WC", "Nightside, WC", "Olde Town, WC", "Ravenwood, WC", "The Commons, WC"
};

const vector<string> krokotopiaNames{
				     "Altar of Kings, KT", "Chamber of Fire, KT", "Djeserit Family Tomb, KT", "Karanahn Barracks, KT", "Krokosphinx, KT", "Temple of Storms, KT", "The Oasis, KT", "The Vault of Ice, KT", "Upper Zigzag, KT", "Well of Spirits, KT"
};

const vector<string> marleyBoneNames{
				     "Barkingham Palace, MB", "Chelsea Court, MB", "Digmoore Station, MB", "Katzenstein's Lab, MB", "Kensington Park, MB", "Newgate Prison, MB", "Regent's Square, MB", "Royal Museum, MB", "Scotland Yard, MB", "The Ironworks, MB"
};

const vector<string> mooShuNames{
				 "Ancient Burial Grounds, MS", "Cave of Solitude, MS", "Crimson Fields, MS", "Hametsu Village, MS", "Jade Palace, MS", "Kishibe Village, MS", "Shirataki Temple, MS", "Tatakai Outpost, MS", "Tree of Life, MS", "Village of Sorrow, MS"
};

const vector<string> dragonSpyreNames{
				      "Dragon's Roost, DS", "Dragonspyre Academy, DS", "Plaza of Conquests, DS", "The Antheneum, DS", "The Basilica, DS", "The Crucible, DS", "The Drake Hatchery, DS", "The Labyrinth, DS", "The Necropolis, DS", "The Tower Archives, DS"
};

const vector<string> grizzleHeimNames{
				      "Frostholm, GH", "Hall of Valor, GH", "Helgrind Warren, GH", "Mirkholm Keep, GH", "Nastrond, GH", "Nidavellir, GH", "Northguard, GH", "Ravenscar, GH", "Savarstaad Pass, GH", "Vigrid Roughland GH", 
};

int main(){
  // create a random number generator with appropriate constants
  randGen* randFloatGen = new randGen(24693, 3517, 131072);

  // generate an appropriate amount of random numbers
  vector<float> spiralAttributes = randFloatGen->getRandomFloats(180);

  // important vector containing all cities
  vector<city*> theSpiral;

  // size of name vectors
  int offset = 10;

  // create all cities with randomized conditions
  for(int i=0; i<offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(wizardCityNames[i], 10*spiralAttributes[3*i+1]+30, 10*spiralAttributes[3*i+2]+30, traffic);
    theSpiral.push_back(newCity);
  }

  for(int i=offset; i<2*offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(krokotopiaNames[i%10], 10*spiralAttributes[3*i+1]+30, 10*spiralAttributes[3*i+2]+40, traffic);
    theSpiral.push_back(newCity);
  }

  
  for(int i=2*offset; i<3*offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(marleyBoneNames[i%10], 10*spiralAttributes[3*i+1]+40, 10*spiralAttributes[3*i+2] + 30, traffic);
    theSpiral.push_back(newCity);
  }

  for(int i=3*offset; i<4*offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(grizzleHeimNames[i%10], 10*spiralAttributes[3*i+1]+ 40, 10*spiralAttributes[3*i+2] + 40, traffic);
    theSpiral.push_back(newCity);
  }

  for(int i=4*offset; i<5*offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(mooShuNames[i%10], 10*spiralAttributes[3*i+1]+ 30, 10*spiralAttributes[3*i+2] + 50, traffic);
    theSpiral.push_back(newCity);
  }

  for(int i=5*offset; i<6*offset; i++){
    char traffic;
    if(spiralAttributes[3*i] < 0.33){
      traffic = 'S';
    }
    else if(spiralAttributes[3*i] > 0.67){
      traffic = 'F';
    }
    else{
      traffic = 'M';
    }
    city* newCity = new city(dragonSpyreNames[i%10], 10*spiralAttributes[3*i+1]+ 40, 10*spiralAttributes[3*i+2] + 50, traffic);
    theSpiral.push_back(newCity);
  }

  cout << "Welcome to the wizard traveler game!" << endl;
  cout << "------------------------------------" << endl;
  cout << "Imagine that you are a wizard in a vast world, known as the spiral. There are many different places within the spiral, some of which harbor forces of good, and others that have become corrupted by evil. You wish to destroy this encroaching darkness, but to do so, you must first embark on a journey to the place of battle." << endl;
  cout << "------------------------------------" << endl;
  cout << "This may seem like a simple task, but along your quest, you must make stops at intervals no longer than 10 miles to avoid starvation and supply defecits. It is also worth noting that travel between places in the spiral does not depend simply upon mileage; traffic flow plays a large role in speed as well." << endl;
  cout << "------------------------------------" << endl;
  cout << "With this in mind, there is a need for a navigation program that can find the shortest path to your destination. Luckily, you have a map containing the coordinates in every city, along with typical traffic conditions therein. Even better, you have a device that uses dijkstra's algorithm with a pairing heap to quickly solve the problem for you!" << endl;
  cout << "------------------------------------" << endl;
  cout << "Now, let's get started. The cities in the spiral now have randomized coordinates and randomized traffic patterns. Please see the menu below to continue: " << endl;
  cout << "------------------------------------" << endl;
  while(true){
    cout << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Get list of cities -> 1" << endl;
    cout << "Get city coordinates -> 2" << endl;
    cout << "Get city traffic -> 3" << endl;
    cout << "Find shortest distance from one city to another -> 4" << endl;
    cout << "Quit -> 5" << endl;
    int choice;
    cout << "Enter a number to continue: ";
    cin >> choice;
    cout << "---------------------------------------------" << endl;

    if(!cin || choice > 5 || choice < 1){
      cout << "Error: Invalid Input!" << endl;
      return 0;
    }

    bool flag;
    string coordName;
    string trafficName;
    string startingCityName;
    string destinationName;
    string target;
    city* startingCity = NULL;
    city* destination = NULL;
    pairing_heap* dijkstraHeap;
    vector<string> itinerary;
    switch(choice){
      // Case 1 is for finding all city names
      case 1:
	  for(int j=0; j<theSpiral.size(); j++){
	    cout<< theSpiral[j]->getName() << endl;
	  }
	  break;
	  // Case 2 is for finding city coordinates
	  
      case 2:
	// take input
	cout << "If the menu is displayed again, the city you entered was not found" << endl;
	cout << "Please enter a city name: ";
	getline(cin>>ws, coordName);
	for(int j=0; j<theSpiral.size(); j++){
	  if(coordName == theSpiral[j]->getName()){
	    cout << "The coordinates of " << theSpiral[j]->getName() << " are (" << theSpiral[j]->getX() << "," << theSpiral[j]->getY() << ")" << endl;
	  }
	}
	break;
	// Case 3 is for finding city traffic
      case 3:
	// take input
	cout << "If the menu is displayed again, the city you entered was not found" << endl;
	cout << "Please enter a city name: ";
	getline(cin>>ws, trafficName);
	for(int j=0; j<theSpiral.size(); j++){
	  if(trafficName == theSpiral[j]->getName()){
	    string traffic;
	    // make the interface understandable
	    if (theSpiral[j]->getTraffic() == 'S'){
	      traffic = "slow";
	    }
	    else if(theSpiral[j]->getTraffic() == 'M'){
	      traffic = "medium";
	    }
	    else{
	      traffic = "fast";
	    }
	    cout << "The traffic of " << theSpiral[j]->getName() << " is " << traffic << endl;
	  }
	}
	break;
	// Case 4 is for dijkstra's algorithm
      case 4:
	// reset variables
	for(int l = 0; l<theSpiral.size(); l++){
	  theSpiral[l]->setPrev(NULL);
	  theSpiral[l]->setNext(NULL);
	  theSpiral[l]->setChild(NULL);
	  theSpiral[l]->setTime(65536);
	  theSpiral[l]->setPrevName("");
	  theSpiral[l]->makeUnknown();
	}
	// starting input
	cout << "If the menu is displayed again, the city you entered was not found" << endl;
	cout << "Please enter your starting city: ";
	getline(cin>>ws, startingCityName);
	for(int i = 0; i<theSpiral.size(); i++){
	  if(theSpiral[i]->getName() == startingCityName){
	    startingCity=theSpiral[i];
	    theSpiral[i]->setTime(0);
	    theSpiral[i]->makeKnown();
	  }
	}
	// create the pairing heap
	// insert everything
	if(startingCity!=NULL){
        dijkstraHeap = new pairing_heap(startingCity);
	for(int i=0; i<theSpiral.size(); i++){
	  if(theSpiral[i]->getName() != startingCity->getName()){
	    dijkstraHeap = dijkstraHeap->insert(theSpiral[i]);
	  }
	}
	while(!dijkstraHeap->empty()){
	  // get the minimum element (shortest path to that city)
	  city* currentCity = dijkstraHeap->getMin();
	  currentCity->makeKnown();
	  cout << currentCity->getTime() << endl;
	  dijkstraHeap = dijkstraHeap->deleteMin();
	  if(dijkstraHeap->empty()){
	    break;
	  }
	  // Check valid edges
	  for(int i=0; i<theSpiral.size(); i++){
	    if(!theSpiral[i]->getKnown()){
	    float edgeWeight = currentCity->calculateTime(theSpiral[i]);
	    if(edgeWeight == -1){
	      // Do nothing
	    }else{
	      // Increase the priority
	      float newWeight = edgeWeight + currentCity->getTime();
	      //
	      if(newWeight < theSpiral[i]->getTime()){
		for(int j=0; j<theSpiral.size(); j++){
		  // orphan the child
		  if(theSpiral[j]->getChild() == theSpiral[i]){
		    if(theSpiral[i]->getNext() != NULL){
		      theSpiral[j]->setChild(theSpiral[i]->getNext());
		    }else{
		      theSpiral[j]->setChild(NULL);
		    }
		  }
		}
		dijkstraHeap = dijkstraHeap->decreaseKey(newWeight, theSpiral[i]);
		// keep track of this for itinerary!
		theSpiral[i]->setPrevName(currentCity->getName());
	      }
	    }
	    }
	  }
	}
	// get ending point input
	cout << "Please enter a destination: ";
	getline(cin>>ws, destinationName);
	// get the float time value
	for(int k=0; k<theSpiral.size(); k++){
	  if(theSpiral[k]->getName() == destinationName && theSpiral[k]){
	    cout << "The shortest path to " << destinationName << " will take " << theSpiral[k]->getTime() << " hours" << endl;
	    destination = theSpiral[k];
	  }
	}
	// back track for the itinerary!
	if(destination!=NULL){
	  if(startingCityName!=destinationName){
	cout << "Itinerary: ";
	flag=true;
        target = destinationName;
	itinerary.push_back(target);
	cout << startingCityName;
	while(flag){
	  for(int n=0; n<theSpiral.size(); n++){
	    if(theSpiral[n]->getName() == destination->getPrevName()){
	      target = destination->getPrevName();
	      if(target == startingCityName){
		flag=false;
	      }
	      else{
		itinerary.push_back(target);
		destination = theSpiral[n];
	      }
	    }
	  }
	}
	for(int m=itinerary.size()-1; m>=0; m--){
	  cout << " -> " << itinerary[m];
	}
	cout << endl;
	}
	}
	}
	break;
	
      case 5:
	return 0;
	break;
	
      }

  }

}
