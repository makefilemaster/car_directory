#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <iterator>
#include <cstdlib>

using namespace std;

//----------------------------------------------------

class car {
	public:
		car() {
			id = count()++;
			year = 0;
		}

		car(int arg) {
			id = arg;
			year = 0;
		}
/* Because we need searching free number for a new car, when delete something
		~car() {
			count()--;
		}
*/
		void printCar() {
			cout << "|----------------------------------------------------|" << endl;
			cout << "|| ID:\t\t\t" << id << "\t\t\t     |" << endl;
			cout << "|| Manufacturer:\t" << manufacturer << "\t\t\t     |" << endl;
			cout << "|| Type:\t\t" << type << "\t\t\t     |" << endl;
			cout << "|| Class:\t\t" << classCar << "\t\t\t     |" << endl;
			cout << "|| Year:\t\t" << year << "\t\t\t     |" << endl;
			cout << "|----------------------------------------------------|" << endl;
		}

		void setYear(int arg) {year = arg;}
		void setManufacturer(string arg) {manufacturer = arg;}
		void setType(string arg) {type = arg;}
		void setClassCar(string arg) {classCar = arg;}
		void setCount(size_t arg) {count() = arg;}

		size_t	getCount() {return count();}
		int 	getId() {return id;}
		int 	getYear() {return year;}
		string	getManufacturer() {return manufacturer;}
		string	getType() {return type;}
		string	getClassCar() {return classCar;}

	private:
		int			id;
		int 		year;
		string		manufacturer;
		string		type;
		string		classCar;
		
		size_t& count() {
			static size_t counter = 1;	//because f*cking function looks like strtol, cin, etc. return '0' if error, but 0 - is valid value for us
			return counter;
		}
		void count(size_t arg) {
			static size_t counter = arg;
		}

};

//----------------------------------------------------
class handler {
	public:
		virtual void handler_function(list <car>*) = 0;
};

class newList:public handler {
	void handler_function(list <car>* tmpList) {
		vector<string> manufacturerDefault = {"BMW", "Audi", "Kia"};
		vector<string> typeDefault = {"Sedan", "Hatchback", "Wagon"};
		vector<string> classCarDefault = {"D", "E", "B"};
		car *  tmpCar;
		for (int i = 0; i < 3; i++) { 
			tmpCar = new car();
			tmpCar->setYear(2012 + i);
			tmpCar->setManufacturer(manufacturerDefault[i]);
			tmpCar->setType(typeDefault[i]);
			tmpCar->setClassCar(classCarDefault[i]);
			cout << "|\t\tNew car was created:\t\t     |" << endl;
			tmpCar->printCar();
			tmpList->push_back(*tmpCar);
		}
	}
};

class add:public handler {
	void handler_function(list <car>* tmpList) {
		car * tmpCar = new car();
		cout << "| Enter year" << endl << "|> ";
		int tmp_int;
		char tmp_str[512];
		char *end;
		cin >> tmp_str;
		tmp_int = strtol(tmp_str, &end,10);
		while (!((tmp_int > 1900) and (tmp_int < 2100))) {
			cout << "| Enter number greater than 1990 and less than 2100  |" << endl << "|> ";
			cin >> tmp_str;
		tmp_int = strtol(tmp_str, &end,10);
		}		
		tmpCar->setYear(tmp_int);
		cout << "| Enter manufacturer" << endl << "|> ";
		cin >> tmp_str;
		tmpCar->setManufacturer(tmp_str);
		cout << "| Enter type" << endl << "|> ";
		cin >> tmp_str;
		tmpCar->setType(tmp_str);
		cout << "| Enter class" << endl << "|> ";
		cin >> tmp_str;
		tmpCar->setClassCar(tmp_str);
		cout << "|----------------------------------------------------|" << endl;
		cout << "|\t\tNew car was created:\t\t     |" << endl;
		tmpCar->printCar();
		tmpList->push_back(*tmpCar);
	}
};

class open:public handler {
	void handler_function(list <car>* tmpList) {
		car * tmpCar;
		string filename = "default_directory";
		char tmp_str[512];
		char *end;
		size_t counter = 0;
		ifstream fin;
		fin.open(filename, ios::beg);
		fin >> counter;
		while (!fin.eof()) {
			fin >> tmp_str;
			tmpCar = new car(strtol(tmp_str, &end,10));
			fin >> tmp_str;
			tmpCar->setYear(strtol(tmp_str, &end,10));
			fin >> tmp_str;
			tmpCar->setManufacturer(tmp_str);
			fin >> tmp_str;
			tmpCar->setType(tmp_str);
			fin >> tmp_str;
			tmpCar->setClassCar(tmp_str);
			tmpList->push_back(*tmpCar);
		}
		tmpList->back().setCount(counter);
		fin.close();
	}
};

class del:public handler {
	void handler_function(list <car>* tmpList) {

		if (tmpList->empty()) {
			cout << "|----------------------------------------------------|" << endl;
			cout << "|\t\tCurrent list of car is EMPTY!\t     |" << endl;
		} else {
			cout << "|----------------------------------------------------|" << endl;
			cout << "| Enter ID for delete car from list:\t\t     |" << endl << "|> ";
			char tmp_str[512];
			char *end;
			int tmp_int;
			int fail = 0;
			cin >> tmp_str;
			tmp_int = strtol(tmp_str, &end, 10);
			while (!((tmp_int > 0) and (tmp_int < tmpList->back().getCount()))) {
				cout << "| Enter number greater than 0 ans less than " << tmpList->back().getCount() << "        |" << endl << "|> ";
				cin >> tmp_str;
			tmp_int = strtol(tmp_str, &end,10);
			}		

			for (list<car> :: iterator i = tmpList->begin(); i != tmpList->end(); i++) {
				if (i->getId() == tmp_int) {
					tmpList->erase(i);
					cout << "| Element successfully deleted!\t\t\t     |" << endl;
					break;
				} else {
					fail++;
					if (fail >= tmpList->size()) {
						cout << "| Element not found! \t\t\t\t     |" << endl;
					}
				}
			}
		}
	} 
};

class edit:public handler {
	void handler_function(list <car>* tmpList) {
		if (tmpList->empty()) {
			cout << "|----------------------------------------------------|" << endl;
			cout << "|\t\tCurrent list of car is EMPTY!\t     |" << endl;
		} else {
			cout << "|----------------------------------------------------|" << endl;
			cout << "| Enter ID for edit car from list:\t\t     |" << endl << "|> ";
			char tmp_str[512];
			char *end;
			int tmp_int;
			int fail = 0;
		
			cin >> tmp_str;
			tmp_int = strtol(tmp_str, &end, 10);
			while (!((tmp_int > 0) and (tmp_int < tmpList->back().getCount()))) {
				cout << "| Enter number greater than 0 ans less than " << tmpList->back().getCount() << "        |" << endl << "|> ";
				cin >> tmp_str;
			tmp_int = strtol(tmp_str, &end,10);
			}	

			 for (list<car> :: iterator i = tmpList->begin(); i != tmpList->end(); i++) {
				if (i->getId() == tmp_int) {
					cout << "| Enter new year" << endl << "|> ";
					cin >> tmp_str;
					tmp_int = strtol(tmp_str, &end,10);
					while (!((tmp_int > 1900) and (tmp_int < 2100))) {
						cout << "| Enter number greater than 1990 and less than 2100  |" << endl << "|> ";
						cin >> tmp_str;
						tmp_int = strtol(tmp_str, &end,10);
					}		
					i->setYear(tmp_int);
					cout << "| Enter new manufacturer" << endl << "|> ";
					cin >> tmp_str;
					i->setManufacturer(tmp_str);
					cout << "| Enter new type" << endl << "|> ";
					cin >> tmp_str;
					i->setType(tmp_str);
					cout << "| Enter new class" << endl << "|> ";
					cin >> tmp_str;
					i->setClassCar(tmp_str);
					cout << "|----------------------------------------------------|" << endl;
					cout << "|\tVehicle parameters have been changed to:     |" << endl;
					i->printCar();
					break;
				} else {
					fail++;
					if (fail >= tmpList->size()) {
						cout << "| Element not found! \t\t\t\t     |" << endl;
					} 
				}
			}
		}
	}
};

class print:public handler {
	void handler_function(list <car>* tmpList) {
		if (tmpList->empty()) {
			cout << "|----------------------------------------------------|" << endl;
			cout << "|\t\tCurrent list of car is EMPTY!\t     |" << endl;
		} else {
			cout << "|----------------------------------------------------|" << endl;
			cout << "|\t\tCurrent list of car:\t\t     |" << endl;
			for (list<car> :: iterator i = tmpList->begin(); i != tmpList->end(); i++) {
				i->printCar();
			}
		}
	}
};

class exitDirectory:public handler {
	void handler_function(list <car>* tmpList) {
		string filename = "default_directory";
		cout << "|----------------------------------------------------|" << endl;
//		cout << "| Enter file name for save list:\t\t     |" << endl << "|> ";
//		cin >> filename;
		if (!tmpList->empty()) {
			ofstream fout;
			fout.open(filename, ios::trunc);
			fout << tmpList->front().getCount();
			for (list<car> :: iterator i = tmpList->begin(); i!= tmpList->end(); i++) {
				fout << endl << i->getId() << endl;
				fout << i->getYear() << endl;
				fout << i->getManufacturer() << endl;
				fout << i->getType() << endl;
				fout << i->getClassCar();
			}
			fout.close();
		}
//		cout << "|----------------------------------------------------|" << endl;
	}
};

class unknow:public handler {
	void handler_function(list <car>* tmpList) {
		cout << "|\t\tCommand not find!\t\t     |" << endl;
	}
};
//----------------------------------------------------

class switcher {
	private:
		bool running;
		map <string, handler*> func;
		handler* default_handler;

	public:
		switcher() {
			running = true;
		}

		bool is_running() {
			return running;
		}

		void set_default(handler* func_handler) {
			default_handler = func_handler;
		}

		void add_command(string key, handler* func_handler) {
			func[key] = func_handler;
		}

		handler* find_command(string key) {
			map<string, handler*> :: iterator i = func.find(key);
			if (i != func.end()) {
				if (dynamic_cast<exitDirectory*>(func[key])) {
					running = false;
				} 
				return func[key]; 				//??? or iterator from map
			} else {
				return default_handler;
			}
		}
};

void printMenu() {
	cout << "|----------------------------------------------------|" << endl;
	cout << "|        You can use the following commands:  	     |" << endl;
	cout << "|       new   - add 3 car into the list              |" << endl;
	cout << "|       open  - open default_directory and load list |" << endl;
	cout << "|       print - print all list of car                |" << endl;
	cout << "|       add   - for manual adding new car in list    |" << endl;
	cout << "|       del   - for delete car from list             |" << endl;
	cout << "|       edit  - for edit car from list               |" << endl;
	cout << "|       exit  - exit with saving current list        |" << endl;
	cout << "|----------------------------------------------------|" << endl;
}

int main() {
	switcher SW; 

	SW.add_command("new", new newList());
	SW.add_command("open", new open());
	SW.add_command("add", new add());
	SW.add_command("del", new del());
	SW.add_command("edit", new edit());
	SW.add_command("print", new print());
	SW.add_command("exit", new exitDirectory());
	SW.set_default(new unknow());

	string arg;

	list <car> listOfCar;

	cout << "|----------------------------------------------------|" << endl;
	cout << "|         	WELCOME TO CAR DIRECTORY   	     |" << endl;

	while (SW.is_running()) {
		printMenu();
		cout << "|> " ;
		cin >> arg;
		SW.find_command(arg)->handler_function(&listOfCar);
	}

	return 0;
}