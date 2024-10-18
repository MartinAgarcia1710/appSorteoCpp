#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

//esta funci�n no usa aleatorio ni shuffle, asigna de manera c�clica las fechas
/*
void asignarGrupos(const std::vector<int>& grupos, const std::vector<std::string>& fechasDisponibles, const std::string& profesor) {
	size_t numFechas = fechasDisponibles.size();
	for (size_t x = 0; x < grupos.size(); x++) {

		std::string fechaAsignada = fechasDisponibles[x % numFechas]; 
		std::cout << "Grupo " << grupos[x] << ", " << profesor << ", Fecha: " << fechaAsignada << std::endl;
	}
}
*/

/* Esto ME VOL� LA CABEZA! Me cost� hasta que entend� la documentaci�n, no pod�a
   encontrar la forma de que se asignen misma cantidad de grupos para cada fecha,
   copi� el c�digo en chat GPT y me modific� el uso de srand por randon_device.
   Y, por otro lado al barajar se equilibran las fechas y aproximadamente son la 
   misma cantidad por d�a. Una locura...
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
		std::cout << "Grupo " << grupos[x] << ", " << profesor << ", Fecha: " << fechaAsignada << std::endl;
	}
}
std::vector<std::string> preguntarFechasDisponibles() {
	/*Las fechas est�n hardcodeadas, si bien ya se sab�a de antemano que son
	  4 fechas decid� usar vector para que se adapte en el futuro a otros sorteos
	  en los que pueda haber m�s d�as disponibles 
	*/
	std::vector<std::string> fechas = { "4/11/2024", "7/11/2024", "11/11/2024", "14/11/2024" };
	std::vector<std::string> fechasDisponibles;
	
	std::cout << "Seleccione las fechas disponibles (1 para s�, 0 para no):\n";
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
	
	/*Cada profesor tiene su colecci�n de grupos que se asignan hardcodeados
	  **Modificar cada colecci�n con los grupos que tengan asignados.
	*/
	std::vector<int> ariel = {5, 11, 20, 40, 32, 44, 88, 77, 46, 100}; 
	std::vector<int> dani = {29, 36}; 
	std::vector<int> angel = {42, 45}; 
	std::vector<int> coco = {47}; 
	std::vector<int> maxi = {60, 70}; 
	std::vector<int> vero = {74, 76}; 
	std::vector<int> mariano = {77}; 
	std::vector<int> brian = {79, 80}; 
	
	/*Declaro un map con los nombres como clave y de valor en cada uno sus
	  colecciones de grupos. Herramienta que no ten�a muy en claro como usar
	  y que me atrev� a probar, parece que funcion�...
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
	
	/*pair, para acceder al map, otra herramienta nueva que aprend� :P
	  first apunta al nombre del profesor y second a su colecci�n 
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
		      << "Saludos!\n"
		      << "Martin Alejandro Garcia";
	
	return 0;
}
