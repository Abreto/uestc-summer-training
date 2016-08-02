var len = Math.ceil(Math.random() * 16);
var digit = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'];
var P = [];

var i = 0;
for(i = 0;i < len;++i)
  P.push(digit[Math.floor(Math.random()*16)]);

console.log(P.join(''));
