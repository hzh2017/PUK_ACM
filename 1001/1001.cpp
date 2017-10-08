#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>


std::string big_num_sum(std::string str1, std::string str2)
{
	int str_len1 = str1.length();
	int str_len2 = str2.length();

	int str_len;
	if(str_len1 < str_len2)
	{
		str_len = str_len2;
		str1.insert(0, str_len2 - str_len1, '0');
	} else
	{
		str_len = str_len1;
		str2.insert(0, str_len1 - str_len2, '0');
	}

	std::string str;
	int per_sum, cy = 0;
	char c;

	for(int i = 1; i <= str_len; i++)
	{
		per_sum = (str1[str_len - i] - 48) + \
				  (str2[str_len - i] - 48) + cy;
		
		if(per_sum >= 10)
		{
			per_sum -= 10;
			cy = 1;
		} else
			cy = 0;

		c = '0' + per_sum;
		str = c + str;
	}

	if(cy == 1)
		str = '1' + str;
	return str;
}

std::string big_num_time(std::string str1, std::string str2)
{
	if(str1 == "")
		return str2;
	else if(str2 == "")
		return str1;
	else
	{
		int str_len1 = str1.length();
		int str_len2 = str2.length();

		std::string str_sum;
		
		for(int i = 1; i <= str_len1; i++)
		{
			std::string str_time;
			int per_time, rem, cy = 0;
			char c;

			for(int j = 1; j <= str_len2; j++)
			{
				per_time = (str1[str_len1 - i] - 48) * (str2[str_len2 - j] - 48) + cy;

				rem = per_time % 10;
				cy = per_time / 10;
				
				c = '0' + rem;
				str_time = c + str_time;
			}

			if(cy > 0)
			{
				c = '0' + cy;
				str_time = c + str_time;
			}

			if(str_sum != "")
			{
				str_time.append(i - 1, '0');
				str_sum = big_num_sum(str_time, str_sum);
			} else
				str_sum = str_time;
		}
		return str_sum;
	}
}


std::string magnititude(std::string str, int exp)
{
	std::string result;
	while(exp)
	{
		if(exp & 0x01)
			result = big_num_time(result, str);
		str = big_num_time(str, str);
		exp = exp >> 1;
	}
	return result;
}


int main()
{
	std::string str;
	int n, dot_idx, dot_num;
	
	struct timeval startTime, endTime;
	float Timeuse;

	while(std::cin >> str >> n)
	{
		gettimeofday(&startTime, NULL);

		dot_idx = str.find('.');
		if(dot_idx != -1)
		{
			while(str[str.length() - 1] == '.' || str[str.length() - 1] == '0')
				str.erase(str.length() - 1);

			dot_num = (str.length() - dot_idx - 1) * n;
			if(str[0] == '0')
			{
				str = magnititude(str.substr(2, str.length()), n);
				str.insert(0, dot_num - str.length(), '0');
				std::cout << "." + str << std::endl;
			}
			else
			{
				str = magnititude(str.substr(0, dot_idx) + str.substr(dot_idx + 1, str.length()), n);
				str.insert(str.length() - dot_num, ".");
				std::cout << str << std::endl;
			}
		}
		else
			std::cout << magnititude(str, n) << std::endl;

		gettimeofday(&endTime, NULL);
		Timeuse = 1000000 * 
			(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
		Timeuse /= 1000000;
		std::cout << "Timeuse : " << Timeuse << std::endl;
	}
}