#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

//esta función no usa aleatorio ni shuffle, asigna de manera cíclica las fechas
/*
void asignarGrupos(const std::vector<int>& grupos, const std::vector<std::string>& fechasDisponibles, const std::string& profesor) {
	size_t numFechas = fechasDisponibles.size();
	for (size_t x = 0; x < grupos.size(); x++) {

		std::string fechaAsignada = fechasDisponibles[x % numFechas]; 
		std::cout << "Grupo " << grupos[x] << ", " << profesor << ", Fecha: " << fechaAsignada << std::endl;
	}
}
*/

/* Esto ME VOLÓ LA CABEZA! Me costó hasta que entendí la documentación, no podía
   encontrar la forma de que se asignen misma cantidad de grupos para cada fecha,
   copié el código en chat GPT y me modificó el uso de srand por randon_device.
   Y, por otro lado al barajar se equilibran las fechas y aproximadamente son la 
   misma cantidad por día. Una locura...
   Esto era lo que verdaderamente buscaba, que sea aleatorio.
   
*/
void asignarGrupos(const std::vector<int>& grupos, const std::vector<std::string>& fechasDisponibles, const std::string& profesor) {
	size_t numFechas = fechasDisponibles.size();
	size_t numGrupos = grupos.size();

	std::vector<std::string> fechasRepetidas;
	
	for (size_t x = 0; x < numGrupos; x++) {
		fechasRepetidas.push_back(fechasDisponibles[x % numFechas]);
	}
	
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(fechasRepetidas.begin(), fechasRepetidas.end(), g);
	
	for (size_t x = 0; x < numGrupos; x++) {
		std::string fechaAsignada = fechasRepetidas[x];
		std::cout << "Grupo " << grupos[x] << ", " << profesor << ", " << fechaAsignada << std::endl;
	}
}
std::vector<std::string> preguntarFechasDisponibles() {
	/*Las fechas están hardcodeadas, si bien ya se sabìa de antemano que son
	  4 fechas decidí usar vector para que se adapte en el futuro a otros sorteos
	  en los que pueda haber más días disponibles 
	*/
	std::vector<std::string> fechas = { "4/11/2024", "7/11/2024", "11/11/2024", "14/11/2024" };
	std::vector<std::string> fechasDisponibles;
	
	std::cout << "Seleccione las fechas disponibles (1 para sí, 0 para no):\n";
	for (const auto& fecha : fechas) {
		int disponible;
		std::cout << fecha << ": ";
		std::cin >> disponible;
		while(disponible < 0 || disponible > 1){
			std::cout << fecha << ": ";
			std::cin >> disponible;
		}
		if (disponible == 1) {
			fechasDisponibles.push_back(fecha);
		}
	}
	
	return fechasDisponibles;
}

int main() {
	
	/*Cada profesor tiene su colección de grupos que se asignan hardcodeados
	  **Modificar cada colección con los grupos que tengan asignados.
	*/
	std::vector<int> ariel = {9, 12,23, 33, 35, 47, 57, 72, 76, 80}; 
	std::vector<int> dani = {18, 40, 44, 52, 65, 75}; 
	std::vector<int> angel = {2, 3, 4, 16, 27, 32, 48}; 
	std::vector<int> coco = {45, 46, 60, 70, 74, 77}; 
	std::vector<int> maxi = {42, 79}; 
	std::vector<int> vero = {5, 11, 20, 29, 36}; 
	std::vector<int> mariano = {6, 7, 21, 25, 38}; 
	std::vector<int> brian = {1, 10, 14, 15, 17, 22, 24, 26, 30, 34, 71}; 
	
	/*Declaro un map con los nombres como clave y de valor en cada uno sus
	  colecciones de grupos. Herramienta que no tenía muy en claro como usar
	  y que me atreví a probar, parece que funcionó...
	*/
	std::map<std::string, std::vector<int>> profesores = {
		{"Ariel", ariel},
		{"Dani", dani},
		{"Angel", angel},
		{"Coco", coco},
		{"Maxi", maxi},
		{"Vero", vero},
		{"Mariano", mariano},
		{"Brian", brian}
	};
	
	std::cout << "\tSorteo de grupos para asignar fecha de defensa de TPI\n"
		      << "\t\t by Martin A. Garcia\n";
	
	/*pair, para acceder al map, otra herramienta nueva que aprendí :P
	  first apunta al nombre del profesor y second a su colección 
	  de equipos. 
	
	*/
	for (const std::pair<std::string, std::vector<int>>& mapProfes : profesores) {
		const std::string& profesor = mapProfes.first;
		const std::vector<int>& grupos = mapProfes.second;
		
		std::cout << "\n--- Profesor: " << profesor << " ---\n";
		std::vector<std::string> fechasDisponibles = preguntarFechasDisponibles();
		
		if (!fechasDisponibles.empty()) {
			std::cout << "Asignando grupos para " << profesor << "...\n";
			asignarGrupos(grupos, fechasDisponibles, profesor);
		} else {
			std::cout << "No hay fechas disponibles para " << profesor << ".\n";
		}
	}
	
	std::cout << "\nEspero que les haya servido! proximanente la app de escritorio con Winforms\n"
		      << "Esta mini app es de uso libre y gratuito, quien la use tiene todo mi consentimiento\n"
		      << "para modificar y tocar lo que quiera. Saludos!\n"
		      << "Martin Alejandro Garcia";
	
	return 0;
}
