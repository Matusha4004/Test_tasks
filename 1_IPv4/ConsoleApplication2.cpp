#include <iostream>
#include <fstream>
#include <string>
#include <map>

struct numbers{

	int* numbers_[4];

	
};


void qwe(std::multimap<numbers, numbers> &e, std::multimap<numbers,numbers>::iterator iter) {
			


}

int main(int argc, char* argv[]) {
	
	std::ifstream file_(argv[1]);
	std::multimap<numbers, numbers> answer;


	int packets_processed_ = 0;
	int packets_containts_ = 0;
	int packets_without_ = 0;

	while (1) {

		char* pocket_lenght_C;
		
		file_.read(pocket_lenght_C,2);
		
		int16_t pocket_lenght = std::atoi(pocket_lenght_C);

		char* pocket_info = new char[14];
		
		file_.read(pocket_info, 14);

		if (pocket_info[12] == 0x08 && pocket_info[13] == 0x00) {
			packets_containts_++;
			char* IP_pocket_info =  new char [20];

			file_.read(IP_pocket_info, 20);

			numbers Istochnik;

			numbers Mesto;

			Istochnik.numbers_[0] = (int*)std::atoi((const char*)IP_pocket_info[12]);
			Istochnik.numbers_[1] = (int*)std::atoi((const char*)IP_pocket_info[13]);
			Istochnik.numbers_[2] = (int*)std::atoi((const char*)IP_pocket_info[14]);
			Istochnik.numbers_[3] = (int*)std::atoi((const char*)IP_pocket_info[15]);


			Mesto.numbers_[0] = (int*)std::atoi((const char*)IP_pocket_info[16]);
			Mesto.numbers_[1] = (int*)std::atoi((const char*)IP_pocket_info[17]);
			Mesto.numbers_[2] = (int*)std::atoi((const char*)IP_pocket_info[18]);
			Mesto.numbers_[3] = (int*)std::atoi((const char*)IP_pocket_info[19]);


			answer.insert(Istochnik, Mesto);
		}
		else {
			packets_without_++;
		}
		packets_processed_++;



		if (file_.eof()) break;
	}

	std::cout << "Packets processed:'\t'" << packets_processed_ << '\n' << "Packets contains IPv4:'\t" << packets_containts_ << '\n' << "Packets without IPv4:'\t'" << packets_without_ << '\n\n';


	


	
	
}

