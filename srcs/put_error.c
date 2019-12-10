#include "lem_in.h"

void		free_path(t_path **s)
{
	t_path	*p;
	t_path	*next;

	p = *s;
	while (p)
	{
		next = p->next;
		free(p);
		p = next;
	}
}

//void 		*put_error1(int type, void **free)
//{
//	if (type == 13 || type == 14)
//		type == 13 ? ft_printf("invalid ants number\n") :
//			ft_printf("ants number can't be zero\n");
//	else if (type == 15 || type == 16)
//		type == 15 ? ft_printf("room name already exist\n") :
//		ft_printf("room name doesn't exist\n");
//	else if (type == 17)
//	{
//		ft_printf("can't reach finish\n");
//		free_path((t_path **)&free);
//	}
//	exit (type);
//}
//
//
//void		*put_error(int type, int lc, void **free)
//{
//	lc ? ft_printf("%d: {red}error: {eoc}", lc) :
//		ft_printf("{red}error: {eoc}");
//	if (type == 0 || type == -1)
//		type == 0 ?ft_printf("can't open file\n")
//			: ft_printf("file is too big\n");
//	else if (type == 1)
//		ft_printf("bad modifier\n");
//	else if (type == 2)
//		ft_printf("bad name\n");
//	else if (type == 3)
//		ft_printf("room or link not well formatted\n");
//	else if (type == 4)
//		ft_printf("empty line\n");
//	else if (type == 5)
//		ft_printf("links can't be modified as a start or end\n");
//	else if (type == 6 || type == 7)
//		ft_printf("several %s rooms\n", type == 6 ? "start" : "end");
//	else if (type == 8)
//		ft_printf("start and end rooms are not given\n");
//	else if (type == 9 || type == 10)
//		ft_printf("no %s room given\n", type == 9 ? "start" : "end");
//	else if (type == 12)
//		ft_printf("out of memory\n");
//	else
//		return (put_error1(type, free));
//	exit (type);
//}

void		put_error(char *err, int lc)
{
	lc ? ft_printf("%d: {red}error: {eoc}", lc) :
		ft_printf("{red}error: {eoc}");
	ft_printf("%s\n", err);
	exit (1);
}