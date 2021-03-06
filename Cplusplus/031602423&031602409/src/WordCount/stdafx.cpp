// stdafx.cpp : source file that includes just the standard includes
// wordcount.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
//分隔符判断并切割字符串
vector<string> splitt(const string &s) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			if (isalnum(s[i]) == 0) {
				++i;
				flag = 0;
				break;
			}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			if (isalnum(s[j]) == 0) {//isalnum()判断输入参数是否为字母或者数字
				flag = 1;
				break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
//比较
int cmp(const pair<string, int>& x, const pair<string, int>& y)
{
	if (x.second != y.second)
		return x.second > y.second;
	else {
		return x.first < y.first;//字典序靠前
	}
}
//字符串转小写
string mytolower(string s) {
	int len = s.size();
	//cout << len<<endl;
	for (int i = 0; i<len; i++) {
		if (s[i] >= 'A'&&s[i] <= 'Z') {
			s[i] = tolower(s[i]);
			//s[i]+=32;//+32转换为小写
			//s[i]=s[i]-'A'+'a';
		}
	}
	return s;
}
//判断字符串是否符合要求
int isstring(string c) {
	if (isdigit(c[0]) != NULL || isdigit(c[1]) != NULL || isdigit(c[2]) != NULL || isdigit(c[3]) != NULL)
		return 0;
	else
		return 1;
}

//统计字符数
int character(char* path) {
	ifstream infile;
	infile.open(path);   //将文件流对象与文件连接起来 
	char c;
	int j = 0;
	int i = 0;
	int count = 0;
	string ff = ".";
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		count++;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	count--;
	//cout << ff;
	//cout << count << endl;
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<string> split = splitt(ff);
    int mark=0;
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		string key = split[i];
		//cout << "before:" << key << endl;
		if (i + 2 <= split.size() && split[i + 1] == "Title"&&key.size() <= 3) {
			count = count - key.size() - 1;
			mark++;
			//cout << count << endl;
		}
	}
	count = count - mark * 19 + 2;
	//cout << count << endl;
	return count;
}
//统计词组/单词数
int word(char* path) {
	ifstream infile;
	infile.open(path);   //将文件流对象与文件连接起来 
	char c;
	int i = 0;
	string ff = ".";
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	ff = mytolower(ff);
	//cout << ff;
	int count = 0;
	int tcount = 0;
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<string> split = splitt(ff);
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		string key = split[i];
		//cout << "before:"<<key << endl;
		if (key == "title") {
			tcount++;
		}
		if (key.size() >= 4 && isstring(key) == 1) {
			count++;
		}
	}
	count = count - 2 * tcount;
	return count;
}
//统计行数
int line(char* path) {
	int lines = 0;
	int count = 0;
	string ff = ".";
	char c;
	int i = 0;
	int flag = 0;
	ifstream infile;
	infile.open(path);   //将文件流对象与文件连接起来 
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c!=' '&&c!='\0'&&c!='\n')
			flag = 1;
		if (c == '\n'&& isdigit(ff[i])==NULL) {
			if (flag==1) {
				lines++;
			}
			flag = 0;
			c = ' ';
		}
		ff += c;
		count++;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	count--;
	if (count != 0 && flag !=0) {
		lines++;
	}
	return lines;
}
//统计词频并输出
vector<pair<string, int>> WordsFrequency(char* path, int w, int m) {
	ifstream infile;
	infile.open(path); //将文件流对象与文件连接起来 
	infile >> noskipws;
	char c;
	int i = 0;
	string ff = ".";
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	ff = mytolower(ff);
	vector<string> split = splitt(ff);
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<pair<string, int>> tVector;
	int lt = 0, rt = 0, la = 0, ra = 0;
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		//cout << split[i] << endl;
		string key = split[i];
		//cout << key << endl;
			//cout << "符合条件的字符串是：" << key << endl;
			int t = 0,a = 0;
			if (key == "title") {
				t = i + 2;
				if (split[i + 1].size() >= 4 && isstring(split[i + 1]) == 1) {
					//tf = split[i + 1];
					lt = i + 1;
				}
				while (!split[t].empty()&&split[t] != "abstract") {
					t++;
				}
				rt = t-1;
				//cout << tf << endl;
				i = t - 1;
				//cout << lt << " " << rt << endl;
				for (int x = lt; x <= rt - m+1; x++) {
					if (split[x].size() >= 4 && isstring(split[x]) == 1)
						key = split[x];
					else
						continue;
					int xx = 1;
					//cout << x << endl;
					while (xx <= m-1) {
						if (split[x + xx].size() < 4 || isstring(split[x + xx]) != 1) {
							key = "#";
							break;
						}
						key += " ";
						key += split[x + xx];
						xx++;
					}
					if (key == "#")
						continue;
					if (m1.count(key) == 0)
					{
						if (w == 1) {
							m1.insert(pair <string, int>(key, 10));
						}
						else {
							m1.insert(pair <string, int>(key, 1));
						}
					}
					else
					{
						if(w==0)
							m1[key]+=1;
						else
							m1[key] += 10;
					}
				}
				continue;
			}
		
			if (key == "abstract") {
				a = i + 2;
				if (split[i + 1].size() >= 4 && isstring(split[i + 1]) == 1) {
					la = i + 1;
				}
				while (!split[a].empty()&&split[a] != "title") {
					a++;
				}
				ra = a-1;
				//cout << af << endl;
				i = a - 1;
				//cout << la << " " << ra << endl;
				for (int y = la; y <= ra-m+1; y++) {
					if (split[y].size() >= 4 && isstring(split[y]) == 1)
						key = split[y];
					else
						continue;
					int yy = 1;
					while (yy <= m-1) {
						//cout<<split[y + yy] << endl;
						if (split[y + yy].size() < 4 || isstring(split[y + yy]) != 1) {
							key = "#";
							break;
						}
						key += " ";
						key += split[y + yy];
						yy++;
					}
					//cout <<y<<" "<<key << endl;
					if (key == "#")
						continue;
					if (m1.count(key) == 0)
					{
						m1.insert(pair <string, int>(key, 1));
					}
					else
					{
						m1[key]++;
					}
				}
			}
		
	}
	//map <string, int>::iterator m1_temp;
	for (map<string, int>::iterator curr = m1.begin(); curr != m1.end(); curr++){
		tVector.push_back(make_pair(curr->first, curr->second));
		//cout << curr->first << " " << curr->second << endl;
	}
	sort(tVector.begin(), tVector.end(), cmp);
	return tVector;
}