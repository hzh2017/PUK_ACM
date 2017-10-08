#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* cSubstr(void* dst, const void* src, int st, int ed)
{
	char* dstS = dst;
	const char* srcS = src;
	for(int i = st; i < ed; i++)
		*dstS++ = srcS[i];
	return dst;
}

void* cAppend(void* dst, const void* src, char c, size_t n, int flag)
{
	/*flag : 1 means append to back, else to front.*/
	int i;
	char* dstS = dst;
	const char* srcS = src;
	if(flag == 1)
	{
		while((*dstS++ = *srcS++) != '\0');
		for(i = 0; i < n; i++)
			*dstS++ = c;
	}
	else
	{
		for(i = 0; i < n; i++)
			*dstS++ = c;
		while((*dstS++ = *srcS++) != '\0');
	}
	printf("dst : %s\n", dst);
	return dst;
}

void* BigNumSum(void* rst, const void* s1, const void* s2)
{
	char* rstS = rst;
	const char* S1 = s1;
	const char* S2 = s2;

	int len_s1 = strlen(S1);
	int len_s2 = strlen(S2);
	int len_s;
	char *new_s1, *new_s2;
	if(len_s1 < len_s2)
	{
		len_s = len_s2;
		new_s1 = malloc(len_s * sizeof(char));
		new_s2 = malloc(len_s * sizeof(char));
		cAppend(new_s1, S1, '0', len_s2 - len_s1, 0);
		memcpy(new_s2, S2, len_s + 1);
	} else
	{
		len_s = len_s1;
		new_s1 = malloc(len_s * sizeof(char));
		new_s2 = malloc(len_s * sizeof(char));
		cAppend(new_s2, S2, '0', len_s1 - len_s2, 0);
		memcpy(new_s1, S1, len_s + 1);
	}
	int i, per_sum, cy = 0;
	char c;
	for(i = len_s - 1; i >= 0; i--)
	{
		per_sum = (new_s1[i] - 48) + (new_s2[i] - 48) + cy;
		if(per_sum >= 10)
		{
			per_sum -= 10;
			cy = 1;
		} else
			cy = 0;
		c = '0' + per_sum;
		rstS[i + 1] = c;
	}
	if(cy == 1)
		rstS[0] = '1';

	rstS[len_s + 1] = '\0';
	return rst;
}

void* BigNumTime(void* rst, const void* s1, const void* s2)
{
	char* rstS = rst;
	const char* S1 = s1;
	const char* S2 = s2;
	if(s1 == "")
		memcpy(rstS, S2, strlen(S2) + 1);
	else if(s2 == "")
		memcpy(rstS, S1, strlen(S1) + 1);
	else
	{
		int len_s1 = strlen(S1);
		int len_s2 = strlen(S2);
		for(int i = len_s1 - 1; i >= 0; i--)
		{
			char* time_s = malloc(200 * sizeof(char));
			int per_time = S1[i] - '0';
			int rem, cy = 0;
			char c;
			if(per_time != 0)
			{
				for(int j = len_s2 - 1; j >= 0; j--)
				{
					rem = (per_time * (S2[j] - '0') + cy) % 10;
					cy = (per_time * (S2[j] - '0') + cy) / 10;
					c = rem + '0';
					char* curS = malloc(strlen(time_s) * sizeof(char));
					memcpy(curS, time_s, strlen(time_s) + 1);
					cAppend(time_s, curS, c, 1, 0);
				}
				if(cy != 0)
				{
					c = cy + '0';
					char* curS = malloc(strlen(time_s) * sizeof(char));
					memcpy(curS, time_s, strlen(time_s) + 1);
					cAppend(time_s, curS, c, 1, 0);
				}
				char* curS = malloc(strlen(time_s) * sizeof(char));
				memcpy(curS, time_s, strlen(time_s) + 1);
				cAppend(time_s, curS, '0', len_s1 - 1 - i, 1);
				printf("time_s : %s\n", time_s);
			}
			if(strlen(rstS) != 0)
			{
				char* curS = malloc(strlen(rstS) * sizeof(char));
				memcpy(curS, rstS, strlen(rstS) + 1);
				BigNumSum(rstS, time_s, curS);
			} else
			{
				memcpy(rstS, time_s, strlen(time_s) + 1);
			}
			printf("rstS : %s\n", rstS);
		}
	}
	return rst;
}

// void* BigNumMag(void* rst, const void* s, int exp)
// {
// 	char* rst = "";
// 	while(exp)
// 	{
// 		if(exp & 0x01)
// 			rst = BigNumTime(rst, str);
// 		str = BigNumTime(str, str);
// 		exp = exp >> 1;
// 	}
// 	str = rst;
// }


// int main()
// {
// 	char s[6] = "";
// 	char* rst = "";
// 	int n, dot_idx, dot_num;

// 	while(scanf("%s %d", s, &n) != EOF)
// 	{
// 		dot_idx = -1;

// 		for(int i = 0; i < strlen(s); i++)
// 			if(s[i] == '.')
// 				dot_idx = i;

// 		if(dot_idx != -1)
// 		{
// 			while(s[strlen(s) - 1] == '.' || s[strlen(s) - 1] == '0')
// 				s[strlen(s) - 1] = '\0';

// 			size_t len_s = strlen(s);
// 			dot_num = (len_s - dot_idx - 1) * n;
// 			if(s[0] == '0')
// 			{
// 				char s1[200] = "";
// 				cSubstr(s1, s + 2, len_s - 2);
// 				rst = BigNumMag(s1, n);
// 				cAppend(rst, '0', dot_num - len_s, 0);
// 				printf("%s\n", strcat(".", rst));
// 			}
// 			else
// 			{
// 				char s1[200] = "", s2[200] = "";
// 				cSubstr(s1, s, dot_idx);
// 				cSubstr(s2, s + dot_idx + 1, len_s - dot_idx - 1);

// 				rst = BigNumMag(strcat(s1, s2), n);

// 				size_t len_rst = strlen(rst);
// 				for(int i = len_rst; i > len_rst - dot_num; i--)
// 					rst[i + 1] = rst[i];
// 				rst[len_rst - dot_num] = '.';
// 				printf("%s\n", rst);
// 			}
// 		}
// 		else
// 			printf("%s\n", BigNumMag(s, n));
// 	}
// }

int main()
{
	char* dst = malloc(200 * sizeof(char));
	char *s1 = "99", *s2 = "9";
	BigNumTime(dst, s1, s2);
	printf("%s\n", dst);
}