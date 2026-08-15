province_name = '湖北'

if province_name == '香港':
    province_name = province_name + '特别行政区'

elif province_name == '北京' or province_name == '上海' or province_name == '天津' or province_name == '重庆':
    province_name = province_name + '市'

else:
    province_name = province_name + '省'

print(province_name)