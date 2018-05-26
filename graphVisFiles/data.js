g = {
  nodes: [
    {id:'0',label:'0',x:0.300000,y:0.000000, size:0.2, color: getColor(1.000000,gradient)},
    {id:'1',label:'1',x:-0.150000,y:0.259808, size:0.2, color: getColor(1.000000,gradient)},
    {id:'2',label:'2',x:-0.150000,y:-0.259808, size:0.2, color: getColor(1.000000,gradient)}
  ],
  edges: [
    {source:'0',target:'1',id:'0',label:'1',type: 'curvedArrow'},
    {source:'1',target:'2',id:'1',label:'2',type: 'curvedArrow'},
    {source:'2',target:'0',id:'2',label:'1',type: 'curvedArrow'}
  ]
}