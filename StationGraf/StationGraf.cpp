#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <string> 
#include <stdio.h> 
#include <list> 
using namespace std;
const int row = 72;//Число вершин в графе 
//ПОИСК КРАЙТЧАЙШЕГО ПУТИ
void Dekstra(int mas[row][row],int ind,int ind1,string name[row],string A,string A1) 
{
	int d[row]; // минимальное расстояние 
	int v[row]; // посещенные вершины 
	int temp, minindex, min;
	int begin_index = ind;
	//Инициализация вершин и расстояний 
	for (int i = 0; i < row; i++)
	{
		d[i] = 10000;
		v[i] = 1;
	}
	d[begin_index] = 0;
	// Шаг алгоритма 
	do
	{
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < row; i++)
		{ // Если вершину ещё не обошли и вес меньше min 
			if ((v[i] == 1) && (d[i] < min))
			{ // Переприсваиваем значения 
				min = d[i];
				minindex = i;
			}
		}
		// Добавляем найденный минимальный вес 
		// к текущему весу вершины 
		// и сравниваем с текущим минимальным весом вершины 
		if (minindex != 10000)
		{
			for (int i = 0; i < row; i++)
			{
				if (mas[minindex][i] > 0)
				{
					temp = min + mas[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);
	// Вывод кратчайших расстояний до вершин 
	cout << "Крайтчайшие расстояния от станции: " << A << " до всех остальных станций " << endl;
	for (int i = 0; i < row; i++)
	{
		cout << name[i] << " -> " << d[i] << endl;
		if (i == ind1)
		{
			cout << "Время в пути от станции: " << A << " до станции " << A1 << "с учетом возможных пересадок равно " << d[i] << " мин " << endl;
		}
	}
	// Восстановление пути 
	int ver[row]; // массив посещенных вершин 
	int end = ind1 - 1; // индекс конечной вершины 
	ver[0] = end + 1; // начальный элемент - конечная вершина 
	int k = 1; // индекс предыдущей вершины 
	int weight = d[end]; // вес конечной вершины 
	while (end != begin_index) // пока не дошли до начальной вершины 
	{
		for (int i = 0; i < row; i++) // просматриваем все вершины 
			if (mas[i][end] != 0) // если связь есть
			{ 
				int temp = weight - mas[i][end]; // определяем вес пути из предыдущей вершины 
		if (temp == d[i]) // если вес совпал с рассчитанным 
		{
			// значит из этой вершины и был переход 
			weight = temp; // сохраняем новый вес 
			end = i;
			// сохраняем предыдущую вершину 
			ver[k] = i + 1; // и записываем ее в массив 
			k++;
		}

	}
}
// Вывод пути (начальная вершина оказалась в конце массива из k элементов) 
cout << "Крайтчайший путь от станции: " << A << " до станции " << A1 << endl;
for (int i = k - 1; i >= 0; i--)
{
	cout << name[ver[i] - 1] << " -> ";
}
cout << A1 << endl;
}
//ВСЕ ВОЗМОЖНЫЕ ПУТИ 
// Направленный граф с использованием представления списка смежности 
class Graph
{
	int V; // Количество вершин в графе 
	list<int>* adj; // Указатель на массив, содержащий списки смежности 
	// Рекурсивная функция, используемая printAllPaths () 
	void printAllPathsUtil(int, int, bool[], int[], int&, string[row]);
public:
	Graph(int V); // Конструктор 
	void addEdge(int u, int v);
	void printAllPaths(int s, int d, string name[row]);
};
Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}
void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v); // Добавить v в список u. 
}
// Печатает все пути от 's' до 'd' 
void Graph::printAllPaths(int s, int d, string name[row])
{
	// Пометить все вершины как не посещенные 
	bool* visited = new bool[V];
	// Создать массив для хранения путей 
	int* path = new int[V];
	int path_index = 0; // Инициализируем path [] как пустой 
	// Инициализируем все вершины как не посещенные 
	for (int i = 0; i < V; i++)
		visited[i] = false;
	// Вызываем рекурсивную вспомогательную функцию для печати всех путей 
	printAllPathsUtil(s, d, visited, path, path_index, name);
}
// Рекурсивная функция для печати всех путей от 'u' до 'd'. 
// visit [] отслеживает вершины в текущем пути. 
// path [] хранит актуальные вершины, 
//path_index является текущим индексом в пути [] 
void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[], int& path_index, string name[row])
{
	// Отметить текущий узел и сохранить его в path [] 
	visited[u] = true;
	path[path_index] = u;
	path_index++;
	// Если текущая вершина совпадает с пунктом назначения, то вывести текущий путь []
	if (u == d) 
	{
		for (int i = 0; i < path_index; i++)
		{
			cout << name[path[i]] << " -> ";
		}
		cout << endl;
	}
else // Если текущая вершина не является пунктом назначения 
{
// Повторение для всех вершин, смежных с текущей вершиной 
list<int>::iterator i;
for (i = adj[u].begin(); i != adj[u].end(); ++i)
if (!visited[*i])
printAllPathsUtil(*i, d, visited, path, path_index, name);
}
// Удалить текущую вершину из path [] и пометить ее как непосещенную 
path_index--;
visited[u] = false;
}
void PositionMas(int mas[row][row], string B, string B1, int s, int d, string name[row])
{
	Graph g(row);
	for (int i = 0; i < 72; i++)
	{
		for (int j = 0; j < 72; j++)
		{
			if (mas[i][j] != 0 || mas[j][i] != 0)
				g.addEdge(mas[i][j], mas[j][i]);
		}
	}
	cout << "Все пути от станции " << B << " до станции " << B1 << endl; g.printAllPaths(s - 1, d - 1, name);
}
//ВЫВОДИМ НА ЭКРАН НАЗВАНИЕ СТАНЦИЙ И ИХ ИНДЕКСЫ 
void NameStations(string name[row])
{
	try {
		//формируем массив станций 
		string n;
		ifstream fin;
		cout << "Введите название файла с названиями станций: "; cin >> n;
		if (typeid(n) != typeid(string))
		{
			throw "Наименование файла должно иметь тип данных string";
		}
		fin.open(n);
		if (!fin.is_open())
			cout << "Файл с названием станций не удалось открыть!" << endl;
		else
			cout << "Файл с названиями станций открыт!" << endl;
		string str;
		while (!fin.eof())
		{
			for (int j = 0; j < row; j++)
			{
				str = "";
				getline(fin, str);
				name[j] = str;
			}
		}
		fin.close();
		cout << "Станции метро и их индексы: " << endl;
		for (int k = 0; k < row; k++) {
			cout << name[k] << " = " << k + 1 << endl;
		}
	}
	catch (...)
	{
		cout << "Проверьте правильность входных данных" << endl;
	}
}
void MassiveStations(int mas[row][row])//ЗАПОЛНЯЕМ МАССИВ СТАНЦИЙ ВРЕМЕНЕМ ПЕРЕЕЗДА МЕЖДУ СТАНЦИЯМИ 
{
	try
	{
		string p;
		ifstream d;
		cout << "Введите имя файла с элементами массива станций: "; cin >> p;
		if (typeid(p) != typeid(string))
		{
			throw "Наименование файла должно иметь тип данных string";
		}
		d.open(p);
		if (!d.is_open())
		{
			cout << "Файл со временем интервала между станциями не удалось открыть!" << endl;
		}
		else if (d.is_open())
		{
			cout << "Файл со временем интервала между станциями открыт!" << endl;
		}
		while (!d.eof())
		{
			for (int k = 0; k < row; k++)
			{
				for (int j = 0; j < row; j++)
				{
					d >> mas[k][j];
				}
			}
		}
		d.close();
	}
	catch (...)
	{
		cout << "Проверьте правильность входных данных" << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	int mas[row][row];
	string name[row];//массив с названием станций 
	int countstation = 0;//подсчет станций 
	int ind = 0, ind1 = 0, s = 0, d = 0;
	string A, A1, find, B, B1;
	NameStations(name);//формируем массив станций 
	MassiveStations(mas);
	//введение начальной и конечной станции 
	try {
		cout << "ПОИСК КРАЙТЧАЙШЕГО ПУТИ: " << endl;
		cout << "Начальная станция: "; cin >> A;
		if (typeid(A) != typeid(string))
		{
			throw "Название начальной станции должно принадлежать типу данных string";
		}
		cout << "Конечная станция: "; cin >> A1;
		if (typeid(A1) != typeid(string))
		{
			throw "Название конечной станции должно принадлежать типу данных string";
		}
		//нахождение индексов начальной и конечной станций 
		for (int y = 0; y < row; y++)
		{
			if (name[y] == A)//если станция содержится в массиве, то 
			{
				cout << "Найдена начальная станция в списке станций!" << endl;
				ind = y + 1;//индекс начальной станции как в файле 
				cout << "Индекс выбранной вами начальной станции: " << ind << endl;
			}
			if (name[y] == A1)
			{
				cout << "Найдена конечная станция в списке станций!" << endl;
				ind1 = y + 1;//индекс конечной станции как в файле 
				cout << "Индекс выбранной вами конечной станции: " << ind1 << endl;
			}
		}
		Dekstra(mas, ind - 1, ind1 - 1, name, A, A1);
		cout << "ПОИСК ВСЕХ ВОЗМОЖНЫХ ПУТЕЙ " << endl;
		cout << "Начальная станция: "; cin >> B;
		if (typeid(B) != typeid(string))
		{
			throw "Название начальной станции должно принадлежать типу данных string";
		}
		cout << "Конечная станция: "; cin >> B1;
		if (typeid(B1) != typeid(string))
		{
			throw "Название конечной станции должно принадлежать типу данных string";
		}
		//нахождение индексов начальной и конечной станций 
		for (int i = 0; i < row; i++)
		{
			if (name[i] == B)//если станция имеется в массиве, то 
			{
				cout << "Начальная вершина найдена в списке станций!" << endl;
				s = i + 1;//индекс начальной станции как в файле 
				cout << "Индекс выбранной вами начальной станции: " << s << endl;
			}
			if (name[i] == B1)
			{
				cout << "Конечная вершина найдена в списке станций!" << endl;
				d = i + 1;//индекс конечной станции как в файле 
				cout << "Индекс выбранной вами конечной станции: " << d << endl;
			}
		}
		PositionMas(mas, B, B1, s, d, name);
	}
	catch (...)
	{
		cout << "Проверьте введенные данные" << endl;
	}
	system("pause");
	return 0;
}