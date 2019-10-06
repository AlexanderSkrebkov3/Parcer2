#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>
#include <fstream>
using namespace std;
class Json {
	any data; // unordered_map<string, any> ob; ��� vector<any> ob;
public:
	// ����������� �� ������, ���������� Json-������.
	Json(const std::string& s)
	{
		bool flag, flag2;
		unordered_map<string, any> Ob1;
		vector<any> Ob2;
		if (s[0] == '{') {
			flag = true; // ������ �� ������
		}
		if (s[0] == '[') {
		flag = false; // ������
		}
		if (!(s[0] == '{' || s[0] == '[')) throw exception("�������� ������ ������");
		void *pointer = nullptr; // ��� ������� null
		string key = ""; // ����
		double x; int a; // ��� ������ ������������ � ����� ��������
			// ���� ���� - ������
			
			int k1=0, k2; // ������� ��� ����������� �� ������
			while(1) // ���� ������ ����� � ��������
			{
				if (flag) // ������ ���� ��� �������
				{
					k1 = (int)s.find("\"", k1); // ������ ������ "
					if (k1 < 0) throw exception("�������� ������ ������");
					k2 = (int)s.find("\"", k1 + 1); // ����� ������ "
					if (k2 < 0) throw exception("�������� ������ ������");
					key = s.substr(k1 + 1, k2 - k1 - 1); // ��������� ����
					k1 = (int)s.find(":", k2 + 1); // ���� : ����� �����
					if (k1 < 0) throw exception("�������� ������ ������");
					
				}
				k1++; // ������ �� : ��� �� [
				string sOb;
				// ���� ������ ��������
				while (1) // ���������� ������� ����������� ����������
				{
					// k1 - ������� ������ ������ � ������������� ������
					if (k1>=s.size()) throw exception("�������� ������ ������");
					if (s[k1] == ',') if (flag) break; else k1++;
					if (s[k1] == '}') if (flag) break; else throw exception("�������� ������ ������");
					if (s[k1] == ']') if (!flag) break; else throw exception("�������� ������ ������");
					if (s[k1] != ' ' && s[k1] != '\n' && s[k1] != '\r' && s[k1] != '\t') // ���� �� �����������
					{
						switch (s[k1]) // ���������� ��� ��������
						{
						case '{': // ��� ������
							k2 = (int)s.find("}", k1 + 1); // ����� �������
							if (k2 < 0) throw exception("�������� ������ ������");
							sOb = s.substr(k1, k2 - k1 + 1); // ������ �������� ������
						//	any_cast<unordered_map<string, any> *>(data)->insert({ key, any_cast<any>(Json(sOb)) });
							if (flag) Ob1.insert({ key, Json(sOb) }); // ����������� ����� ������������ ��� ���������� �������
							else Ob2.push_back(Json(sOb));// ����������� ����� ������������ ��� ���������� �������
							k2++; // ������� � ���� ������� �� }
							break;
						case '[': // �������� ������
						{
							k2 = (int)s.find("]", k1 + 1); // ����� �������
							if (k2 < 0) throw exception("�������� ������ ������");
							sOb = s.substr(k1, k2 - k1 + 1); // ������ �������� ������
							if (flag) Ob1.insert({ key, Json(sOb) }); // ����������� ����� ������������ ��� ���������� �������
							else Ob2.push_back(Json(sOb));// ����������� ����� ������������ ��� ���������� �������
							k2++; // ������� � ���� ������� �� ]
							break;
						}
						case '\"': // �������� ������
							k2 = (int)s.find("\"", k1 + 1); // ����� ������
							if (k2 < 0) throw exception("�������� ������ ������");
							sOb = s.substr(k1+1, k2 - k1 - 1); // �������� - ������� ������
							if (flag) Ob1.insert({ key, sOb });
							else Ob2.push_back(sOb);
						    k2++; // ������� � ���� ������� �� " (������ ������)
							break;
						case 'f':   case 't':  // �������� true ��� false
							if (s[k1]=='f') flag2 = false;
							else flag2 = true;
							k2 = k1 + 1; 
							while (isalpha(s[k2])) k2++; // ���������� ������� - �����
							if (flag) Ob1.insert({ key, flag2 });
							else Ob2.push_back(flag2);
							break;
						case 'n':   // null
							k2 = k1 + 1;
							while (isalpha(s[k2])) k2++; // ���������� ������� - �����
							if (flag) Ob1.insert({ key, pointer });
							else Ob2.push_back(pointer);
							break;
						default:
							// ������ �������� ��� �����
							stringstream ss(s.substr(k1));
							ss >> x;
							if (ss.fail()) // ������ ������
								throw exception("�������� ������ ������");
							// ��������� ����� ����� ��� ������������
							a = x;
							if (flag)
							{
								if (a == x) Ob1.insert({ key, a }); // �����
								else Ob1.insert({ key, x }); // ������������
							}
							else
								if (a == x) Ob2.push_back(a); // �����
								else Ob2.push_back(x); // ������������

							k2 = k1 + 1;
							while (s[k2] >= '0' && s[k2] <= '9' || s[k2] == '.') k2++; // ���������� ����� ����� ����� � .

						} // switch (s[k])
						k1 = k2;
						
					} // if (s[k] != ' ' && s[k] != '\n' && s[k] != '\r'); // ���� �� �����������
					else k1++; // ������� ����������� ����������
					if (s[k1] == ']') break;
				} // while(1)
			
				if (s[k1] == ']' || s[k1] == '}') break;
			} // while(1)

		if (flag) data = Ob1;
		else data = Ob2;
	}

	void print()
	{
		if (is_object()) // ������ �������
		{   
			cout << endl << "{";
			int i = 0;
			for (auto pos : any_cast<unordered_map<string, any>>(data))
			{
				if (i > 0) cout << ", ";
				cout << endl << pos.first<<": "; // ����
				// ������ ��������
			    if (pos.second.type() == typeid(string)) cout << any_cast<string>(pos.second);
				if (pos.second.type() == typeid(int)) cout << any_cast<int>(pos.second);
				if (pos.second.type() == typeid(double)) cout << any_cast<double>(pos.second);
				if (pos.second.type() == typeid(bool)) cout << any_cast<bool>(pos.second);
				if (pos.second.type() == typeid(void *)) cout << "null";
				if (pos.second.type() == typeid(Json)) any_cast<Json>(pos.second).print();
				i++;
			}
			cout << endl << "}";
		}
		else // ������ �������
		{
			cout << endl << "[";
			int i = 0;
			for (auto pos : any_cast<vector<any>>(data))
			{
				if (i > 0) cout << ", ";
				// ������ �������� �������
				if (pos.type() == typeid(string)) cout << any_cast<string>(pos);
				if (pos.type() == typeid(int)) cout << any_cast<int>(pos);
				if (pos.type() == typeid(double)) cout << any_cast<double>(pos);
				if (pos.type() == typeid(bool)) cout << any_cast<bool>(pos);
				if (pos.type() == typeid(void *)) cout << "null";
				if (pos.type() == typeid(Json)) any_cast<Json>(pos).print();
				i++;
			}
			cout <<  "]";
		}
	}

	
	// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
	bool is_array() const
	{
		if (data.type() == typeid(vector<any>)) return true;
		else return false;
	}
	// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
	bool is_object() const
	{
		if (data.type() != typeid(vector<any>)) return true;
		else return false;
	}

	// ����� ���������� �������� �� ����� key, ���� ��������� �������� JSON-��������.
	// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
	// ���� ��������� �������� JSON-��������, ������������ ����������.
	std::any& operator[](const std::string& key)
	{
		if (data.type() == typeid(vector<any>)) throw exception("�������� ���");
		return any_cast<unordered_map<string, any>>(data)[key];
	}

	// ����� ���������� �������� �� ������� index, ���� ��������� �������� JSON-��������.
	// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
	// ���� ��������� �������� JSON-��������, ������������ ����������.
	std::any& operator[](int index)
	{
		if (typeid(data) != typeid(vector<any>)) throw exception("�������� ���");
		return any_cast<vector<any>>(data)[index];
	}


	// ����� ���������� ������ ������ Json �� ������, ���������� Json-������.
	static Json parse(const std::string& s)
	{
		Json JS(s);
		return JS;
	}

	// ����� ���������� ������� ������ Json �� �����, ����������� Json-������ � ��������� �������.
	static Json parseFile(const std::string& path_to_file)
	{
		ifstream F(path_to_file);
		string Str = "";
		while (!F.eof())
		{
			string S1;
			F >> S1;
			Str += S1;
		}
		//cout << endl << Str << endl;
		F.close();
		return parse(Str);
	}
};

int main()
{
	// ������ ��� ������������
	try
	{
		string teststr = "{\
		\"lastname\" : \"Ivanov\",\
			\"firstname\" : \"Ivan\",\
			\"age\" : 25,\
			\"islegal\" : false,\
			\"marks\" : [\
				4, 5, 5, 5, 2, 3\
			],\
			\"address\" : {\
					\"city\" : \"Moscow\",\
						\"street\" : \"Vozdvijenka\"\
				}\
	}";
		string str1 = "[\"Hello1\", 1.5, \"Hello3\", 2]";
		string str2 = "{\"Hello\": true, \"World\": false}";

		//	Json Js1(teststr);
		Json Js1 = Json::parseFile("Proba.txt");
		Js1.print();
		cout << endl << any_cast<string>(Js1["lastname"]);
	}
	catch (exception e)
	{
		cout << endl << "Exception: " << e.what();
	}
	return 0;
}