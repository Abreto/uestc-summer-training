var n = Math.ceil(Math.random()*100);
var m = Math.ceil(Math.random()*100);
var i = 0, j = 0;
var ch = ['.', 'T'];

console.log(n + " " + m);
for(i = 0;i < n;++i)
{
  var line = [];
  for(j = 0;j < m;++j)
    line.push(ch[Math.round(Math.random())]);
  console.log( line.join("") );
}
