#include <iostream>
#include <fstream>
#include <string>

struct numbers{

	int* numbers_[4];

	
	bool operator==(numbers first) {
		return this->numbers_ == first.numbers_;

	}

};


struct Node {



	numbers first_;

	numbers second_;

	int count = 0;
	

	Node* next = nullptr;

	Node(numbers first, numbers second) {
		first_ = first;
		second_ = second;
		count++;
	}

	Node() {

	}
};


struct Lists {

	Node* began = nullptr;


	void add(numbers first, numbers second) {

		if (began == nullptr) {
			began = new Node;
			began->first_ = first;
			began->second_ = second;
			began->count++;
		}
		else {

			Node* work_with = began;
			while (work_with->next != nullptr) {
				if (work_with->first_ == first && work_with->second_ == second) {
					work_with->count++;
					break;
				}
				else if (work_with->next == nullptr) {
					work_with->next = new Node(first,second);
				}



			}


		}

	}

	void print() {
		Node* work_with = began;

		while (work_with->next!=nullptr)
		{
			std::cout << work_with->first_.numbers_[0] << '.' << work_with->first_.numbers_[1] << '.' << work_with->first_.numbers_[2] << '.' << work_with->first_.numbers_[3] << " -> ";

			std::cout << work_with->second_.numbers_[0] << '.' << work_with->second_.numbers_[1] << '.' << work_with->second_.numbers_[2] << '.' << work_with->second_.numbers_[3] << "          ";

			std::cout << work_with->count;


			work_with = work_with->next;
		}
	}
};

bool hasIPv4(const unsigned char* ethernetHeader) {

	return (ethernetHeader[12] == 0x08 && ethernetHeader[13] == 0x00);

}

int main(int argc, char* argv[]) {
	
	std::ifstream file_("C:/Users/Matusha/source/repos/ConsoleApplication3/x64/Debug/packets.sig", std::ios::binary);
	Lists answer;

	int packets_processed_ = 0;
	int packets_containts_ = 0;
	int packets_without_ = 0;

	


	while (!file_.eof()) {

		
		
		unsigned char pocket_info[14];
		
		uint16_t pocket_lenght;

		file_.read(reinterpret_cast<char*>(&pocket_lenght), 2);
		
		file_.read(reinterpret_cast<char*>(pocket_info), 14);

		if (hasIPv4(pocket_info)) {
			packets_containts_++;

			unsigned char* IP_pocket_info[20];

			file_.read(reinterpret_cast<char*>(IP_pocket_info), 20);

			numbers Istochnik;

			numbers Mesto;

			Istochnik.numbers_[0] = reinterpret_cast<int*>(IP_pocket_info[12]);
			Istochnik.numbers_[1] = reinterpret_cast<int*>(IP_pocket_info[13]);
			Istochnik.numbers_[2] = reinterpret_cast<int*>(IP_pocket_info[14]);
			Istochnik.numbers_[3] = reinterpret_cast<int*>(IP_pocket_info[15]);


			Mesto.numbers_[0] = reinterpret_cast<int*>(IP_pocket_info[16]);
			Mesto.numbers_[1] = reinterpret_cast<int*>(IP_pocket_info[17]);
			Mesto.numbers_[2] = reinterpret_cast<int*>(IP_pocket_info[18]);
			Mesto.numbers_[3] = reinterpret_cast<int*>(IP_pocket_info[19]);

			answer.add(Istochnik, Mesto);

		}
		else {
			packets_without_++;
		}
		packets_processed_++;

		file_.ignore(pocket_lenght - 34);

	}

	std::cout << "Packets processed:\t" << packets_processed_ << '\n' << "Packets contains IPv4:\t" << packets_containts_ << '\n' << "Packets without IPv4:\t" << packets_without_ << '\n';


	
	answer.print();

	
	
}

