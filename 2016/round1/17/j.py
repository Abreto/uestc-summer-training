# UESTC 2016 Summer Training #17 Div.2. Problem J, by Abreto, 20160728.
datas = {};

for x in range(6):
    name = raw_input();
    phone = raw_input();
    price = raw_input();
    if not datas.has_key(phone):
        trip = {'buyers':[name], 'count':1, 'price':price};
        datas[phone] = trip;
    else:
        havebought = 0;
        for person in datas[phone]['buyers']:
            if person == name:
                havebought = 1;
                break;
        if not havebought:
            datas[phone]['buyers'].append(name);
            datas[phone]['count'] += 1;
        if price < datas[phone]['price']:
            datas[phone]['price'] = price;

phonename = "";
maxnusers = 0;
minprice = 0;

print datas;

for phon in datas:
    if datas[phon]['count'] > maxnusers:
        phonename = phon;
        maxnusers = datas[phon]['count'];
        minprice = datas[phon]['price'];
    elif datas[phon]['count'] == maxnusers:
        if datas[phon]['price'] < minprice:
            phonename = phon;
            minprice = datas[phon]['price'];

print phonename;
