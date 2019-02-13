/*
Дана последовательность различных целых чисел, заканчивающаяся 0.
Построить из чисел бинарное дерево поиска.
Вывести дерево на экран.
По данному числу k провести поиск в БДП(бинарное дерево поиска).
Для данного числа q удалить вершину из дерева с информационной частью, равной q/
Автор: Ситдиков А.Ф.
*/
#include <iostream>
#include <iomanip>
using namespace std;

struct tree
{
	int info;
	tree * left, * right;
};

// Прототипы функций
tree * MakeTree1(int level);
void PrintTree(tree * root, int level =0);
tree * SearchTree(tree * root,int k);
void DeleteNode(tree * &root, int k);
void PrintTree(tree * root, int level);						
void FindClone(tree * root);								
void SearchClone(tree * root, int level, int SearchLevel, int & TempPosition, int *LevelValues);
int MaxLevel(tree * root, int level);	
void SrchInArr(int * LevelValues, int TempPosition);


void main()
{
	setlocale( LC_ALL,"Russian" );
	tree * root = NULL;

	root = MakeTree1(0);
	cout << "Tree:" << endl;
	PrintTree(root);

	cout << "Максимальный уровень " << MaxLevel(root, 0) << endl;

	FindClone(root);


	system("pause");
	return;
}

//функция создает ПРОИЗВОЛЬНОЕ БИНАРНОЕ ДЕРЕВО
tree * MakeTree1(int level)
{
	char c ;
	cout << setw(5*level) << " " << "Create a node? (y/n)" << endl;
	cin >> c;
	if (c == 'y')
	{
		tree * p = new tree;
		cout << setw(5*level) << " " << "Input a number:";
		cin >> p -> info;
		cout << setw(5*level) << " " << "Left tree of " << p -> info << endl;
		p -> left = MakeTree1(level + 1);
		cout << setw(5*level) << " " << "Right tree of " << p -> info << endl;
		p -> right = MakeTree1(level + 1);
		return p;
	}
	else
		return NULL;
}



// Функция печатает на консольном экране бинарное дерево root
void PrintTree(tree * root, int level)
{
	if(root != NULL)
	{
		PrintTree(root -> left, level + 1);
		cout << setw(3*level) << root -> info << endl;
		PrintTree(root -> right, level + 1);
	}
}





//Вычисляет максимальный уровень бинарного дерева
int MaxLevel(tree * root, int level)
{
	if (root)
	{
		int left = MaxLevel(root -> left, level +1);	
		int right = MaxLevel(root -> right, level +1);	
		return max(left,right);							
	}
	else
		return level-1;
}

//Находит элементы-двойники
void FindClone(tree * root)
{
	if (root)
	{
		for (int i = 0; i <= MaxLevel(root,0); i++)	//Проходим циклом от корня дерева до максимального уровня
		{
			int *LevelValues = new int[50];	//Значения текущего уровня(не более 50-ти)
			int TempPosition = 0;			//Текущая позиция в массиве значений
			SearchClone(root, 0, i, TempPosition, LevelValues);
			cout << "Элементы находящиеся на " << i << "-м уровне:" <<endl;
			for(int j = 0; j < TempPosition; j++)
				cout << LevelValues[j]<< " ";
			cout << endl;
			SrchInArr(LevelValues,TempPosition);
		}
	}
	return;
}

//Поиск клонов по уровням
void SearchClone(tree * root, int level, int SearchLevel , int & TempPosition, int *LevelValues)
{
	if (root)
	{
		if (level <= SearchLevel)	
		{
			if (level == SearchLevel)
			{
				LevelValues[TempPosition] = root -> info;
				TempPosition ++;
			}
			else
			{
				SearchClone(root->left, level+1, SearchLevel, TempPosition, LevelValues);
				SearchClone(root->right, level+1, SearchLevel, TempPosition, LevelValues);
			}
		}
		else
			return;
	}
	return;
}

//Поиск двойников по массиву
void SrchInArr(int * LevelValues, int TempPosition)
{
	bool Check = false;	//Наличие двойников
	int Temp;			//Текущий элемент массива
	for (int i = 0; i < TempPosition-1; i++)
	{
		Temp = LevelValues[i];
		for (int j = i+1; j < TempPosition; j++)
			if (Temp == LevelValues[j])
			{
				cout << "Найден двойник: " << Temp << endl;
				Check = true;
			}
	}
	if (!Check)
		cout << "Двойники не найдены" << endl;

	return;
}