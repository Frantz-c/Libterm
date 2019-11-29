/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utf8_generator.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 15:17:32 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 19:57:52 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUFLEN	1024

void	get_sample(char lead, char buf[], int size)
{
	unsigned int i, n;
	char		c;

	if (size == 2)
	{
		for (i = 0, c = 0; c < 50; i += 2, c++)
		{
			buf[i] = lead;
			buf[i + 1] = (0x80 | (rand() % 64));
		}
		buf[i] = 0;
	}
	else if (size == 3)
	{
		for (i = 0, c = 0; c < 50; i += 3, c++)
		{
			buf[i] = lead;
			buf[i + 1] = (0x80 | (rand() % 64));
			buf[i + 2] = (0x80 | (rand() % 64));
		}
		buf[i] = 0;
	}
	else if (size == 4)
	{
		for (i = 0, c = 0; c < 50; i += 4, c++)
		{
			buf[i] = lead;
			buf[i + 1] = (0x80 | (rand() % 64));
			buf[i + 2] = (0x80 | (rand() % 64));
			buf[i + 3] = (0x80 | (rand() % 64));
		}
		buf[i] = 0;
	}
}

void	latin1(char buf[])
{
	get_sample(0xC2, buf, 2);
	printf("latin1   (0xC2) -> %s\n", buf);
}

void	latin2(char buf[])
{
	get_sample(0xC3, buf, 2);
	printf("latin2   (0xC3) -> %s\n", buf);
}

void	latin3(char buf[])
{
	get_sample(0xC4, buf, 2);
	printf("latin3   (0xC4) -> %s\n", buf);
}

void	latin4(char buf[])
{
	get_sample(0xC5, buf, 2);
	printf("latin4   (0xC5) -> %s\n", buf);
}

void	latin5(char buf[])
{
	get_sample(0xC6, buf, 2);
	printf("latin5   (0xC6) -> %s\n", buf);
}

void	latin6(char buf[])
{
	get_sample(0xC7, buf, 2);
	printf("latin6   (0xC7) -> %s\n", buf);
}

void	latin7(char buf[])
{
	get_sample(0xC8, buf, 2);
	printf("latin7   (0xC8) -> %s\n", buf);
}

void	ipa1(char buf[])
{
	get_sample(0xC9, buf, 2);
	printf("ipa1     (0xC9) -> %s\n", buf);
}

void	ipa2(char buf[])
{
	get_sample(0xCA, buf, 2);
	printf("ipa2     (0xCA) -> %s\n", buf);
}

void	ipa3(char buf[])
{
	get_sample(0xCB, buf, 2);
	printf("ipa3     (0xCB) -> %s\n", buf);
}

void	accents1(char buf[])
{
	get_sample(0xCC, buf, 2);
	printf("accents1 (0xCC) -> %s\n", buf);
}

void	accents2(char buf[])
{
	get_sample(0xCD, buf, 2);
	printf("accents2 (0xCD) -> %s\n", buf);
}

void	greek1(char buf[])
{
	get_sample(0xCE, buf, 2);
	printf("greek1   (0xCE) -> %s\n", buf);
}

void	greek2(char buf[])
{
	get_sample(0xCF, buf, 2);
	printf("greek2   (0xCF) -> %s\n", buf);
}

void	cyril1(char buf[])
{
	get_sample(0xD0, buf, 2);
	printf("cyril1   (0xD0) -> %s\n", buf);
}

void	cyril2(char buf[])
{
	get_sample(0xD1, buf, 2);
	printf("cyril2   (0xD1) -> %s\n", buf);
}

void	cyril3(char buf[])
{
	get_sample(0xD2, buf, 2);
	printf("cyril3   (0xD2) -> %s\n", buf);
}

void	cyril4(char buf[])
{
	get_sample(0xD3, buf, 2);
	printf("cyril4   (0xD3) -> %s\n", buf);
}

void	cyril5(char buf[])
{
	get_sample(0xD4, buf, 2);
	printf("cyril5   (0xD4) -> %s\n", buf);
}

void	armeni(char buf[])
{
	get_sample(0xD5, buf, 2);
	printf("armeni   (0xD5) -> %s\n", buf);
}

void	hebrew1(char buf[])
{
	get_sample(0xD6, buf, 2);
	printf("hebrew1  (0xD6) -> %s\n", buf);
}

void	hebrew2(char buf[])
{
	get_sample(0xD7, buf, 2);
	printf("hebrew2  (0xD7) -> %s\n", buf);
}

void	arabic1(char buf[])
{
	get_sample(0xD8, buf, 2);
	printf("arabic1  (0xD8) -> %s\n", buf);
}

void	arabic2(char buf[])
{
	get_sample(0xD9, buf, 2);
	printf("arabic2  (0xD9) -> %s\n", buf);
}

void	arabic3(char buf[])
{
	get_sample(0xDA, buf, 2);
	printf("arabic3  (0xDA) -> %s\n", buf);
}

void	arabic4(char buf[])
{
	get_sample(0xDB, buf, 2);
	printf("arabic4  (0xDB) -> %s\n", buf);
}

void	syriac(char buf[])
{
	get_sample(0xDC, buf, 2);
	printf("syriac   (0xDC) -> %s\n", buf);
}

void	arabic5(char buf[])
{
	get_sample(0xDD, buf, 2);
	printf("arabic5  (0xDD) -> %s\n", buf);
}

void	thaana(char buf[])
{
	get_sample(0xDE, buf, 2);
	printf("thanna   (0xDE) -> %s\n", buf);
}

void	n_ko(char buf[])
{
	get_sample(0xDF, buf, 2);
	printf("n'ko     (0xDF) -> %s\n", buf);
}

void	indic(char buf[])
{
	get_sample(0xE0, buf, 3);
	printf("indic    (0xE0) -> %s\n", buf);
}

void	misc(char buf[])
{
	get_sample(0xE1, buf, 3);
	printf("misc     (0xE1) -> %s\n", buf);
}

void	symbol(char buf[])
{
	get_sample(0xE2, buf, 3);
	printf("symbol   (0xE2) -> %s\n", buf);
}

void	kana(char buf[])
{
	get_sample(0xE3, buf, 3);
	printf("kana     (0xE3) -> %s\n", buf);
}

void	cjk1(char buf[])
{
	get_sample(0xE4, buf, 3);
	printf("cjk1     (0xE4) -> %s\n", buf);
}

void	cjk2(char buf[])
{
	get_sample(0xE5, buf, 3);
	printf("cjk2     (0xE5) -> %s\n", buf);
}

void	cjk3(char buf[])
{
	get_sample(0xE6, buf, 3);
	printf("cjk3     (0xE6) -> %s\n", buf);
}

void	cjk4(char buf[])
{
	get_sample(0xE7, buf, 3);
	printf("cjk4     (0xE7) -> %s\n", buf);
}

void	cjk5(char buf[])
{
	get_sample(0xE8, buf, 3);
	printf("cjk5     (0xE8) -> %s\n", buf);
}

void	cjk6(char buf[])
{
	get_sample(0xE9, buf, 3);
	printf("cjk6     (0xE9) -> %s\n", buf);
}

void	asian(char buf[])
{
	get_sample(0xEA, buf, 3);
	printf("asian    (0xEA) -> %s\n", buf);
}

void	hangul1(char buf[])
{
	get_sample(0xEB, buf, 3);
	printf("hangul1  (0xEB) -> %s\n", buf);
}

void	hangul2(char buf[])
{
	get_sample(0xEC, buf, 3);
	printf("hangul2  (0xEC) -> %s\n", buf);
}

void	hangul3(char buf[])
{
	get_sample(0xED, buf, 3);
	printf("hangul3  (0xED) -> %s\n", buf);
}

void	pua(char buf[])
{
	get_sample(0xEE, buf, 3);
	printf("pua      (0xEE) -> %s\n", buf);
}

void	forms(char buf[])
{
	get_sample(0xEF, buf, 3);
	printf("forms    (0xEF) -> %s\n", buf);
}

void	smp(char buf[])
{
	get_sample(0xF0, buf, 4);
	printf("smp      (0xF0) -> %s\n", buf);
}

void	square1(char buf[])
{
	get_sample(0xF1, buf, 4);
	printf("◻︎        (0xF1) -> %s\n", buf);
}

void	square2(char buf[])
{
	get_sample(0xF2, buf, 4);
	printf("◻︎ 2      (0xF2) -> %s\n", buf);
}

void	ssp(char buf[])
{
	get_sample(0xF3, buf, 4);
	printf("ssp      (0xF3) -> %s\n", buf);
}

void	spu(char buf[])
{
	get_sample(0xF4, buf, 4);
	printf("spu      (0xF4) -> %s\n", buf);
}


void	(*func[])(char*) = {
	&latin1, &latin2, &latin3, &latin4, &latin5, &latin6, &latin7,
	&ipa1, &ipa2, &ipa3,
	&accents1, &accents2,
	&greek1, &greek2,
	&cyril1, &cyril2, &cyril3, &cyril4, &cyril5,
	&armeni,
	&hebrew1, &hebrew2,
	&arabic1, &arabic2, &arabic3, &arabic4, 
	&syriac, &arabic5,
	&thaana,
	&n_ko,
	&indic,	// 3 bytes
	&misc,
	&symbol,
	&kana,
	&cjk1, &cjk2, &cjk3, &cjk4, &cjk5, &cjk6,
	&asian,
	&hangul1, &hangul2, &hangul3,
	&pua,
	&forms,
	&smp,	// 4 bytes
	&square1, &square2,
	&ssp,
	&spu,
	NULL
};

int		main(void)
{
	char	sample[BUFLEN];
	
	srand(time(NULL));
	for (unsigned int i = 0; func[i]; i++)
	{
		func[i](sample);
	}
}
