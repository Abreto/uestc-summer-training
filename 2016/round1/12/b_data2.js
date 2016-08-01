var n = Math.ceil(Math.random()*100);
var m = Math.ceil(Math.random()*100);
var i = 0, j = 0;
var ch = ['.', 'T'];

console.log(n + " " + m);
for(i = 0;i < n;++i)
{
  var line = [];
  var dots = 0;
  var ts = 0;

  dots = Math.floor(Math.random()*(m+1));
  for(j = 0;j < dots;++j)
    line.push('.');
  ts = Math.floor( Math.random() * (m-dots+1) );
  for(j = 0;j < ts;++j)
    line.push('T');
  for(j = 0;j < m - dots - ts;++j)
    line.push('.');

  console.log( line.join("") );
}
