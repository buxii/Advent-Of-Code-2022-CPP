#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include "split.h"

struct node {
	std::string name;
	std::size_t size=0;
	std::vector<std::unique_ptr<node>> children;
	node* parent = nullptr;

	bool is_file() { return children.empty(); }
	bool is_dir() { return !is_file(); }

	node(node* parent, std::string name) : parent(parent), name(std::move(name)) {}
	node(node* parent, std::string name, std::size_t size) : parent(parent), name(std::move(name)), size(size) {}
};

class command_line {
public:
	void process_data(std::ifstream& in) { // Creem arbre
		if(in.is_open()) {
		std::vector<std::string> vec_lectura;
		while (!in.eof()) { // Llegim fitxer i coloquem en un vector de strings el qual s'acabarà convertint en un vector de vectors d'strings
			std::string str;
			getline(in, str);
			vec_lectura.push_back(str);
		}
		current_ = std::begin(vec_lectura);
		end_ = std::end(vec_lectura);
		while (current_ != std::end(vec_lectura)) {
			auto commands = split<std::string>(*current_, " ");
			if (commands[1] == "cd") change_dir(commands[2]);
			else if (commands[1] == "ls") list_dir();
			
			++current_;
		}
		
		}
		else {
			std::cerr << "FILE CAN'T BE OPENED" << std::endl;
		}
		in.close();

		// RESOLDRE A:
		calcular_size_A(root_.get());
		std::cout << "A: " << suma_total_ << std::endl; // Calculem size total de tots aquells que no sumen 100.000

		// RESOLDRE B:
		std::size_t espai_buit = 70000000 - root_->size ;
		std::size_t a_buidar = 30000000 - espai_buit;
		calcular_size_B(root_.get(), a_buidar);
		std::cout << "B: " << min_size_ << std::endl;
	}

private:
	std::vector<std::string>::iterator current_;
	std::vector<std::string>::iterator end_;
	
	std::unique_ptr<node> root_ = std::make_unique<node>(nullptr, "/");
	node* current_dir_;
	
	std::size_t suma_total_ = 0;
	std::size_t min_size_= std::numeric_limits<std::size_t>::max();

private:
	std::size_t calcular_size_B(node* curr,const std::size_t &a_buidar) {
		for (const auto& child_ptr : curr->children) {
			if (child_ptr->is_dir()) {
				node* child = child_ptr.get();
				if(child->size>=a_buidar) min_size_ = std::min(min_size_, child->size);
				min_size_ = std::min(min_size_, calcular_size_B(child, a_buidar));
			}
		}

		return min_size_;

	}

	std::size_t calcular_size_A(node* curr) {
		std::size_t suma = curr->size;
		for (const auto& child_ptr : curr->children) {
			if (child_ptr->is_dir()) {
				node* child = child_ptr.get();
				suma += calcular_size_A(child);
			}
		}

		if (suma <= 100000) {
			suma_total_ += suma;
		}
		return 0; // Tornem 0 per dirli a la funcio que no volem sumar res mes, si tornessim suma cada cop es sumaria suma a suma_total_ i quedaria 96021 a mes de 95437
	}

	node* mkdir(std::string name) {
		auto nou_node = std::make_unique<node>(current_dir_, std::move(name));
		auto node_ptr = nou_node.get();
		current_dir_->children.push_back(std::move(nou_node));
		return node_ptr;

	}
	node* mkfile(std::string name, std::size_t size) {
		auto nou_node = std::make_unique<node>(current_dir_, std::move(name), size);
		auto node_ptr = nou_node.get();
		current_dir_->children.push_back(std::move(nou_node));

		//Propaguem cap a dalt per actualitzar a tots els pares del file size!
		for (node* parent = current_dir_; parent != nullptr; parent = parent->parent) {
			parent->size += node_ptr->size;
		}

		return node_ptr;
	}

	void change_dir(std::string_view name) {
		if (name == "/") {
			current_dir_ = root_.get(); // we are at our outermost
		}
		else if (name == ".."){
			current_dir_ = current_dir_->parent;
		}
		else {
			// Busquem si ja hem anat abans al dir en questio
			bool trobat = false;
			for (const auto& it : current_dir_->children) {
				if (it->name == name) {
					current_dir_ = it.get();
					trobat = true;
					break;
				}
			}
			// Sinó, creem un nou dir
			if (!trobat) {
				current_dir_ = mkdir(std::string(name));
			}
		}
	}
	void list_dir() {
		++current_;
		
		for (current_; current_ != end_ && current_->front() != '$';++current_) {
			auto entrada = split<std::string>(*current_, " ");
			if (entrada[0] == "dir") {
				mkdir(entrada[1]);
			}
			else {
				mkfile(entrada[1], std::stoi(entrada[0]));
			}
		}

		--current_; //perque sino ens saltem una comanda, ja que just al sortir fara ++current_!
	}
};


int main() {
	std::ifstream in("input.txt");
	command_line cl;
	cl.process_data(in);

	return 0;
}