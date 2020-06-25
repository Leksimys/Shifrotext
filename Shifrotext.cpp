#include <iostream>
#include <regex>
#include "nlohmann/json.hpp"
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
using json = nlohmann::json;
class base
{
public:
	virtual void createKey(string text) = 0;
	virtual void findText() = 0;
};
class rePlace : public base
{
public:
	void findText()
	{
		cout << "Enter path to document with key" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		string key;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(Replace)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				key = result[2];
				findCypher(key);
			}
			else
			{
				cout << "Key is not for Replace" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void createKey(string text)
	{
		bool trigger = false;
		vector<int> key;
		for (int a = 0; a < key.size(); a++)
		{
			int num = rand() % key.size();
			for (int i = 0; i < text.size(); i++)
			{
				if (key[i] == num)
				{
					num = rand() % key.size();
					i = -1;
					continue;
				}
				if (i == text.size() - 1)
					key[a] = num;
			}
		}
		for (int a = 0; a < 33; a++)
			cout << "\b";
		string chos;
		cout << "Key was generated. Print it on display? (Y/N)";
		while (1)
		{
			cin >> chos;
			cmatch result;
			regex regular("([\\w])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "Y")
				{
					for (int a = 0; a < key.size(); a++)
						cout << key[a];
					cout << endl;
					break;
				}
				else if (chos == "N")
				{
					break;
				}
				else
				{
					cout << "Incorrect answer. Try again" << endl;
					continue;
				}
			}
			else
			{
				cout << "Incorrect symbol" << endl;
				system("pause");
				exit(0);
			}
		}
		saveKey(key, text);
	}
private:
	void findCypher(string keyTemp)
	{
		cout << "Enter path to document with cypher" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(encrypt)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(Replace)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				string cypherTemp = result[2];
				string key;
				string cypher;
				for (int a = 7; ; a++)
				{
					if (keyTemp[a] == '}')
						break;
					else
					{
						key.push_back(keyTemp[a]);
					}
				}
				for (int a = 10; ; a++)
				{
					if (cypherTemp[a] == '}')
						break;
					else
						cypher.push_back(cypherTemp[a]);
				}
				decrypt(key, cypher);
			}
			else
			{
				cout << "Key is not for Replace" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void decrypt(string key, string cypher)
	{
		vector<int> keyA;
		string text;
		for (int a = 0; a < cypher.size(); a++)
			text.push_back(' ');
		string temp;
		string numStr;
		int num;

		for (int a = 0; a < key.size(); a++)
		{
			int b = a;
			while (1)
			{
				if (key[b] == ',')
				{
					a = b;
					break;
				}
				numStr.push_back(key[b]);
				b++;
			}
			num = stoi(numStr);
			keyA.push_back(num);
			numStr.clear();
		}
		int tempT;
		for (int a = 0; a < cypher.size(); a++)
		{
			tempT = keyA[a];
			text[a] = cypher[tempT];
		}
		cout << "Enter path to save text" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(.+)""(.txt)");
		if (regex_search(path.c_str(), result, regular))
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << text;
			}
			else
			{
				cout << "Error. Wrong path" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Use .txt document extension" << endl;
			system("pause");
			exit(0);
		}

	}
	void saveKey(vector<int> key, string text)
	{
		cout << "Enter path for save key in document" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(.key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << "Replace {Key: ";
				for (int a = 0; a < key.size(); a++)
					dock << key[a] << ",";
				dock << "}";
				cout << "Key was saved" << endl;
				crypt(key, text);
			}
			else
			{
				cout << "Error. Cannot open this document" << endl;
				system("pause");
				exit(0);
			}
		}
	}
	void crypt(vector<int> key, string text)
	{
		string cypher;
		for (int a = 0; a < text.size(); a++)
			cypher.push_back(' ');
		int i = 0;
		for (int a = 0; a < text.size(); a++)
		{
			int place = key[i];
			cypher[place] = text[a];
			i++;
		}
		cout << "Cypher was created" << endl;
		cout << "Enter path to save cypher: " << endl;
		string path;
		cin >> path;
		regex regular("(\.)""(encrypt)");
		cmatch result;
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << "Replace {cypher: ";
				for (int a = 0; a < key.size(); a++)
					dock << cypher[a];
				dock << "}";
				cout << "Cypher was saved" << endl;
			}
			else
			{
				cout << "Error. Cannot open this document" << endl;
				system("pause");
				exit(0);
			}
		}
	}
};
class change : public base
{
public:
	void findText()
	{
		cout << "Enter path to document with key" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		string key;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(.+)""(Change)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				findCypher(keyDoc);
			}
			else
			{
				cout << "Key is not for Change" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Cannot find document" << endl;
			system("pause");
			exit(0);
		}
	}
	void createKey(string text)
	{
		string key;
		for (int a = 0; a < text.size(); a++)
			key.push_back(' ');
		fstream alph("my_alphabet.alph");
		string alphDoc;
		if (alph.is_open())
			getline(alph, alphDoc);
		string alphStr;
		for (int a = 7; a < alphDoc.size(); a++)
		{
			if (alphDoc[a] == ',' || alphDoc[a] == '[' || alphDoc[a] == ']' || alphDoc[a] == '[' || alphDoc[a] == '{' || alphDoc[a] == '}' || alphDoc[a] == '"')
			{
				continue;
			}
			else
			{
				alphStr.push_back(alphDoc[a]);
			}
		}
		int sym;
		int i = 0;
		for (int a = 0; a < key.size(); a++)
		{
			sym = rand() % alphStr.size();
			for (int b = 0; b < key.size(); b++)
			{
				if (key[b] == alphStr[sym])
				{
					a--;
					break;
				}
				else if (key[b] != alphStr[sym])
				{
					if (b == key.size() - 1)
					{
						key[i] = alphStr[sym];
						i++;
						break;
					}
					continue;
				}
			}
		}
		cout << "Key was generated. Print it on display?(Y/N)";
		string chos;
		while (1)
		{
			cin >> chos;
			cmatch result;
			regex regular("([\\w])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "Y")
				{
					for (int a = 0; a < key.size(); a++)
						cout << key[a];
					cout << endl;
					break;
				}
				else if (chos == "N")
				{
					break;
				}
				else
				{
					cout << "Incorrect answer. Try again" << endl;
					continue;
				}
			}
			else
			{
				cout << "Incorrect symbol" << endl;
				system("pause");
				exit(0);
			}
		}
		saveKey(key, text, alphStr);
	}
private:
	void findCypher(string key)
	{
		cout << "Enter path to document with cypher" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(encrypt)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string cypherDoc;
		if (text.is_open())
		{
			getline(text, cypherDoc);
			cmatch result;
			regex regular("(.+)""(Change)""(.+)");
			if (regex_search(cypherDoc.c_str(), result, regular))
			{
				decrypt(key, cypherDoc);
			}
			else
			{
				cout << "Key is not for Change" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void decrypt(string key, string cypher)
	{
		fstream alph("my_alphabet.alph");
		string alphDoc;
		if (alph.is_open())
			getline(alph, alphDoc);
		string alphStr;
		for (int a = 7; a < alphDoc.size(); a++)
		{
			if (alphDoc[a] == ',' || alphDoc[a] == '[' || alphDoc[a] == ']' || alphDoc[a] == '[' || alphDoc[a] == '{' || alphDoc[a] == '}' || alphDoc[a] == '"')
			{
				continue;
			}
			else
			{
				alphStr.push_back(alphDoc[a]);
			}
		}
		bool trigger = false;
		string text; //35--14-- (-5)
		for (int a = 32; ; a++)
		{
			if (a == cypher.size() - 2)
			{
				break;
			}
			for (int b = 0; b < alphStr.size(); b++)
			{
				if (b == alphStr.size() - 1)
				{
					text.push_back(cypher[a]);
					trigger = true;
					break;
				}
				else if (cypher[a] == alphStr[b])
				{
					trigger = false;
					break;
				}
			}
			if (trigger == true)
			{
				trigger = false;
				continue;
			}
			for (int b = 35; b < key.size(); b += 11)
			{
				if (cypher[a] == key[b])
				{
					text.push_back(key[b - 5]);
					break;
				}
				else
					continue;
			}
		}
		string path;
		cout << "Enter path to save text" << endl;
		cin >> path;
		ofstream dock;
		dock.open(path, std::ios::app);
		if (dock.is_open())
		{
			dock << text << endl;
		}
	}
	void saveKey(string cypher, string text, string alph)
	{
		string key;
		for (int a = 0; a < alph.size(); a++)
		{
			for (int b = 0; b < text.size(); b++)
			{
				if (alph[a] == text[b])
				{
					key.push_back(cypher[b]);
					break;
				}
				else
					continue;
			}
		}
		string alphText;
		for (int a = 0; a < alph.size(); a++)
		{
			for (int b = 0; b < text.size(); b++)
			{
				if (alph[a] == text[b])
				{
					alphText.push_back(text[b]);
					break;
				}
				else
					continue;
			}
		}
		cout << "Enter path for save key in document" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << "'alg_type': 'Change','key':[";
				for (int a = 0; a < alphText.size(); a++)
				{
					dock << "['" << alphText[a] << "'" << ", '" << key[a] << "'],";
				}
				dock << "]}";
				cout << "Key was saved" << endl;
				dock.close();
				string cypherTemp;
				fstream keyT(path);
				string keyDoc;
				if (keyT.is_open())
				{
					getline(keyT, keyDoc);
				}
				for (int a = 0; a < text.size(); a++)
				{
					for (int b = 30; b < keyDoc.size(); b += 11)
					{
						if (text[a] == keyDoc[b])
						{
							cypherTemp.push_back(keyDoc[b + 5]);
							break;
						}
						else
							continue;
					}
				}
				crypt(cypherTemp, alph, text);
			}
			else
			{
				cout << "Error. Cannot open this document" << endl;
				system("pause");
				exit(0);
			}
		}
	}
	void crypt(string cypher, string alph, string text)
	{
		cout << "Enter path to save cypher: " << endl;
		string path;
		cin >> path;
		regex regular("(\.)""(encrypt)");
		cmatch result;
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			int counter = 0;
			ofstream dock;
			dock.open(path, std::ios::app);
			bool trigger = false;
			if (dock.is_open())
			{
				dock << "{'alg_type': 'Change', 'text': '";
				for (int a = 0; a < text.size(); a++)
				{
					for (int b = 0; b < alph.size(); b++)
					{
						if (text[a] == alph[b])
						{
							dock << cypher[a - counter];
							break;
						}
						else if (b == alph.size() - 1)
						{
							dock << text[a];
							counter++;
							break;
						}
					}
				}
				dock << "'}";
				cout << "Cypher was saved" << endl;
			}
			else
			{
				cout << "Error. Cannot open this document" << endl;
				system("pause");
				exit(0);
			}
		}
	}
};
class gamming : public base
{
public:
	void findText()
	{
		cout << "Enter path to document with key" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		string key;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(.+)""(Gamming)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				findCypher(keyDoc);
			}
			else
			{
				cout << "Key is not for Change" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Cannot find document" << endl;
			system("pause");
			exit(0);
		}
	}
	void createKey(string text)
	{
		fstream alph("my_alphabet.alph");
		string alphDoc;
		if (alph.is_open())
			getline(alph, alphDoc);
		string alphStr;
		for (int a = 7; a < alphDoc.size(); a++)
		{
			if (alphDoc[a] == ',' || alphDoc[a] == '[' || alphDoc[a] == ']' || alphDoc[a] == '[' || alphDoc[a] == '{' || alphDoc[a] == '}' || alphDoc[a] == '"')
			{
				continue;
			}
			else
			{
				alphStr.push_back(alphDoc[a]);
			}
		} //alphsize = 51
		string key;
		int sym;
		bool trigger = false;
		for (int a = 0; a < text.size(); a++)
		{
			for (int b = 0; b < alphStr.size(); b++)
			{
				if (text[a] == alphStr[b])
				{
					trigger = false;
					break;
				}
				else if (b == alphStr.size() - 1)
				{
					trigger = true;
					break;
				}
			}
			if (trigger == true)
			{
				continue;
			}
			sym = rand() % 52;
			key.push_back(alphStr[sym]);
		}
		cout << "Key was generated. Print it on display?(Y/N)";
		string chos;
		while (1)
		{
			cin >> chos;
			cmatch result;
			regex regular("([\\w])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "Y")
				{
					cout << key << endl;
					cout << endl;
					break;
				}
				else if (chos == "N")
				{
					break;
				}
				else
				{
					cout << "Incorrect answer. Try again" << endl;
					continue;
				}
			}
			else
			{
				cout << "Incorrect symbol" << endl;
				system("pause");
				exit(0);
			}
		}
		saveKey(key, text, alphStr);
	}
private:
	void saveKey(string key, string text, string alph)
	{
		cout << "Enter path for save key in document" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << "'alg_type': 'Gamming','key':[" << key;
				dock << "]}";
				cout << "Key was saved" << endl;
			}
			crypt(key, text, alph);
		}
	}
	void crypt(string key, string text, string alph)
	{
		string cypher;
		vector<int> numKey;
		vector<int> numText;
		for (int a = 0; a < text.size(); a++)
		{
			for (int b = 0; b < alph.size(); b++)
			{
				if (text[a] == alph[b])
				{
					if (text[a] == ' ')
						break;
					numText.push_back(b);
					continue;
				}
				else
					continue;
			}
		}
		for (int a = 0; a < key.size(); a++)
		{
			for (int b = 0; b < alph.size(); b++)
			{
				if (key[a] == alph[b])
				{
					numKey.push_back(b);
					continue;
				}
				else
					continue;
			}
		}
		vector<int> numCypher;
		for (int a = 0; a < numKey.size(); a++)
		{
			numCypher.push_back(numKey[a] + numText[a]);
			if (numCypher[a] > 51)
			{
				numCypher[a] = numCypher[a] - 51;
			}
		}
		for (int a = 0; a < numCypher.size(); a++)
		{
			for (int b = 0; b < alph.size(); b++)
			{
				if (numCypher[a] == b)
				{
					cypher.push_back(alph[b]);
				}
			}
		}
		cout << "Enter path to save cypher: " << endl;
		string path;
		cin >> path;
		regex regular("(\.)""(encrypt)");
		cmatch result;
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream textTemp(path);
		string textDoc;
		if (textTemp.is_open())
		{
			cout << "Error. This document exist already" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			int counter = 0;
			bool trigger = false;
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << "{'alg_type': 'Gamming', 'text': '";
				for (int a = 0; a < text.size(); a++)
				{
					for (int b = 0; b < alph.size(); b++)
					{
						if (text[a] == alph[b])
						{
							dock << cypher[a - counter];
							break;
						}
						else if (b == alph.size() - 1)
						{
							dock << text[a];
							counter++;
							break;
						}
					}
				}
				dock << "'}";
				cout << "Cypher was saved" << endl;
			}
			else
			{
				cout << "Error. Cannot open this document" << endl;
				system("pause");
				exit(0);
			}
		}
	}
	void findCypher(string key)
	{
		cout << "Enter path to document with cypher" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(encrypt)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string cypherDoc;
		if (text.is_open())
		{
			getline(text, cypherDoc);
			cmatch result;
			regex regular("(.+)""(Gamming)""(.+)");
			if (regex_search(cypherDoc.c_str(), result, regular))
			{
				decrypt(key, cypherDoc);
			}
			else
			{
				cout << "Key is not for Change" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void decrypt(string keyT, string cypherT)
	{
		fstream alph("my_alphabet.alph");
		string alphDoc;
		if (alph.is_open())
			getline(alph, alphDoc);
		string alphStr;
		for (int a = 7; a < alphDoc.size(); a++)
		{
			if (alphDoc[a] == ',' || alphDoc[a] == '[' || alphDoc[a] == ']' || alphDoc[a] == '[' || alphDoc[a] == '{' || alphDoc[a] == '}' || alphDoc[a] == '"')
			{
				continue;
			}
			else
			{
				alphStr.push_back(alphDoc[a]);
			}
		}
		string key;
		vector<int> numKey;
		vector<int> numCypher;
		vector<int> numText;
		for (int a = 29; a < keyT.size(); a++)
		{
			if (keyT[a] == ']')
				break;
			else
			{
				key.push_back(keyT[a]);
			}
		}
		string cypher;
		for (int a = 33; a < cypherT.size(); a++)
		{
			if (cypherT[a] == '\'')
				break;
			else
			{
				cypher.push_back(cypherT[a]);
			}
		}
		for (int a = 0; a < key.size(); a++)
		{
			for (int b = 0; b < alphStr.size(); b++)
			{
				if (key[a] == alphStr[b])
				{
					numKey.push_back(b);
				}
			}
		}
		for (int a = 0; a < cypher.size(); a++)
		{
			for (int b = 0; b < alphStr.size(); b++)
			{
				if (cypher[a] == alphStr[b])
				{
					numCypher.push_back(b);
				}
			}
		}
		for (int a = 0; a < key.size(); a++)
		{
			numText.push_back(numCypher[a] - numKey[a]);
			if (numText[a] < 0)
			{
				numText[a] += 51;
			}
		}
		string textTemp;
		int counter = 0;
		bool trigger = false;
		for (int a = 0; a < numText.size(); a++)
		{
			textTemp.push_back(alphStr[numText[a - counter]]);
		}
		string text;
		for (int a = 0; a < cypher.size(); a++)
		{
			for (int b = 0; b < alphStr.size(); b++)
			{
				if (cypher[a] == alphStr[b])
				{
					text.push_back(textTemp[a - counter]);
					break;
				}
				else if (b == alphStr.size() - 1)
				{
					counter++;
					text.push_back(cypher[a]);
					break;
				}
			}
		}
		string path;
		cout << "Enter path to save text" << endl;
		cin >> path;
		ofstream dock;
		dock.open(path, std::ios::app);
		if (dock.is_open())
		{
			dock << text << endl;
		}
	}
};
class crypt
{
public:
	void cryptFunc(base& method, string text)
	{
		method.createKey(text);
	}
	void decrypt(base& method)
	{
		method.findText();
	}
};
int main()
{
	crypt cr;
	rePlace a;
	change b;
	gamming c;
	while (1)
	{
		srand(time(NULL));
		cout << "Choose the option" << endl;
		cout << "1. Decrypt" << endl;
		cout << "2. Create key and crypt text" << endl;
		cout << "3. Exit" << endl;
		int cho;
		cin >> cho;
		if (cho == 1)
		{
			cout << "Choose the kind of crypt" << endl;
			cout << "1. Replacement" << endl;
			cout << "2. Gamming" << endl;
			cout << "3. Transposition" << endl;
			cin >> cho;
			if (cho == 1)
			{
				cr.decrypt(a);
			}
			else if (cho == 2)
			{
				cr.decrypt(c);
			}
			else if (cho == 3)
			{
				cr.decrypt(b);
			}
			else
			{
				cout << "Incorrect option" << endl;
				system("pause");
				break;
			}
		}
		else if (cho == 2)
		{
			cout << "Choose the kind of crypt" << endl;
			cout << "1. Replacement" << endl;
			cout << "2. Gamming" << endl;
			cout << "3. Transposition" << endl;
			string chos;
			cin >> chos;
			cmatch result;
			regex regular("([\\d])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "1")
				{
					cout << "Enter path of document with text: " << endl;
					string path;
					cin >> path;
					fstream text(path);
					string textDoc;
					int check = 0;
					if (text.is_open())
					{
						while (getline(text, textDoc))
						{
							check++;
							if (check > 1)
							{
								cout << "Sorry. As you use pre-pre-pre-alpha-alpha version you cant put here a document with 2 or more strings. Advice: put all you text in one string please C:" << endl;
								system("pause");
								return 0;
							}
						}
						getline(text, textDoc);
						cr.cryptFunc(a, textDoc);
					}
					else
					{
						cout << "Error. The document was not found" << endl << endl;
						system("pause");
						return 0;
					}
				}
				else if (chos == "2")
				{
					cout << "Enter path of document with text: " << endl;
					string path;
					cin >> path;
					fstream text(path);
					string textDoc;
					int check = 0;
					if (text.is_open())
					{
						while (getline(text, textDoc))
						{
							check++;
							if (check > 1)
							{
								cout << "Sorry. As you use pre-pre-pre-alpha-alpha version you cant put here a document with 2 or more strings. Advice: put all you text in one string please C:" << endl;
								system("pause");
								return 0;
							}
						}
						getline(text, textDoc);
						cr.cryptFunc(c, textDoc);
					}
					else
					{
						cout << "Error. The document was not found" << endl << endl;
						system("pause");
						return 0;
					}
				}
				else if (chos == "3")
				{
					cout << "Enter path of document with text: " << endl;
					string path;
					cin >> path;
					fstream text(path);
					string textDoc;
					int check = 0;
					if (text.is_open())
					{
						while (getline(text, textDoc))
						{
							check++;
							if (check > 1)
							{
								cout << "Sorry. As you use pre-pre-pre-alpha-alpha version you cant put here a document with 2 or more strings. Advice: put all you text in one string please C:" << endl;
								system("pause");
								return 0;
							}
						}
						getline(text, textDoc);
						cr.cryptFunc(b, textDoc);
					}
					else
					{
						cout << "Error. The document was not found" << endl << endl;
						system("pause");
						return 0;
					}
				}
				else
				{
					cout << "Incorrect option" << endl;
					system("pause");
					return 0;
				}
			}
			else
			{
				cout << "Incorrect option" << endl;
				system("pause");
				return 0;
			}

		}
		else
			return 0;
	}
}
