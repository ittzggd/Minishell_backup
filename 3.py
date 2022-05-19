dict_first = {'사과' : 30, '배': 15, '감': 10, '포도': 10}
dict_second = {'사과': 5, '감': 25, '배': 15, '귤': 25}

def merge_dict(dict_first, dict_second):
	
	for key in dict_second:
		if key in dict_first:
			dict_second[key] = dict_second[key] + dict_first[key]

	result_dict = {**dict_first, **dict_second}
	print(result_dict)

print(merge_dict(dict_first, dict_second))
