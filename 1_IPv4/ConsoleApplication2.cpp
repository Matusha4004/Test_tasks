#include <iostream>
#include <fstream>
#include <string>

struct IP_space{

	int numbers_[4];

	
	bool operator==(IP_space& other) {
		for (int i = 0; i < 4; ++i) {
			if (this->numbers_[i] != other.numbers_[i]) {
				return false;
			}
		}
		return true;
	} 

};


struct Node {



	IP_space first_;

	IP_space second_;

	int count = 0;
	

	Node* next = nullptr;

	Node(IP_space first, IP_space second) {
		first_ = first;
		second_ = second;
		count++;
	}

	Node() {

	}
};


struct Lists {

	Node* began = nullptr;


	void add(IP_space first, IP_space second) {

		if (began == nullptr) {
			began = new Node;
			began->first_ = first;
			began->second_ = second;
			began->count++;
		}
		else {

			Node* current = began;
			while (current != nullptr) {
				if (current->first_ == first && current->second_ == second) {
					current->count++;
					return;
				}
				if (current->next == nullptr) {
					break;
				}
				current = current->next;
			}
			current->next = new Node(first, second);


		}

	}

	void print() {
		Node* work_with = began;

		while (work_with->next!=nullptr)
		{
			std::cout << work_with->first_.numbers_[0] << '.' << work_with->first_.numbers_[1] << '.' << work_with->first_.numbers_[2] << '.' << work_with->first_.numbers_[3] << "\t->\t";

			std::cout << work_with->second_.numbers_[0] << '.' << work_with->second_.numbers_[1] << '.' << work_with->second_.numbers_[2] << '.' << work_with->second_.numbers_[3] << '\t' << '\t';

			std::cout << work_with->count << '\n';


			work_with = work_with->next;
		}
	}
};

bool hasIPv4(const unsigned char* ethernet_header) {

	return (ethernet_header[12] == 0x08 && ethernet_header[13] == 0x00);

}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		return 1;
	}


	std::ifstream file_(argv[1], std::ios::binary);
	if (!file_.is_open()) {
		return 2;
	}

	Lists IP_counter_list;

	int packets_processed_ = 0;
	int packets_containts_ = 0;
	int packets_without_ = 0;

	


	while (!file_.eof()) {

		
		
		unsigned char packet_info[14];
		
		uint16_t packet_lenght;

		file_.read(reinterpret_cast<char*>(&packet_lenght), sizeof(packet_lenght));
		
		file_.read(reinterpret_cast<char*>(packet_info), sizeof(packet_info));

		packet_lenght -= sizeof(packet_info);

		if (hasIPv4(packet_info)) {

			packets_containts_++;

			unsigned char IP_pocket_info[20]; 

			file_.read(reinterpret_cast<char*>(IP_pocket_info), sizeof(IP_pocket_info));

			packet_lenght -= sizeof(IP_pocket_info);

			IP_space source;
			for (int i = 0; i < 4; ++i) {
				source.numbers_[i] = static_cast<int>(IP_pocket_info[12 + i]);
			}

			IP_space Destination;
			for (int i = 0; i < 4; ++i) {
				Destination.numbers_[i] = static_cast<int>(IP_pocket_info[16 + i]);
			}

			IP_counter_list.add(source, Destination);
		}
		else {
			packets_without_++;
		}
		packets_processed_++;

		file_.ignore(packet_lenght);

	}

	std::cout << "Packets processed:\t" << packets_processed_ << '\n' << "Packets contains IPv4:\t" << packets_containts_ << '\n' << "Packets without IPv4:\t" << packets_without_ << '\n';


	
	IP_counter_list.print();

	
	
}

