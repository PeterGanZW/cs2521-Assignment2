g = {
  nodes: [
    {id:'0',label:'0',x:0.300000,y:0.000000, size:0.2, color: getColor(1.000000,gradient)},
    {id:'1',label:'1',x:0.150000,y:0.259808, size:0.2, color: getColor(1.000000,gradient)},
    {id:'2',label:'2',x:-0.150000,y:0.259808, size:0.2, color: getColor(1.000000,gradient)},
    {id:'3',label:'3',x:-0.300000,y:0.000000, size:0.2, color: getColor(1.000000,gradient)},
    {id:'4',label:'4',x:-0.150000,y:-0.259808, size:0.2, color: getColor(1.000000,gradient)},
    {id:'5',label:'5',x:0.150000,y:-0.259808, size:0.2, color: getColor(1.000000,gradient)}
  ],
  edges: [
    {source:'0',target:'3',id:'0',label:'1',type: 'curvedArrow'},
    {source:'1',target:'2',id:'1',label:'2',type: 'curvedArrow'},
    {source:'2',target:'4',id:'2',label:'2',type: 'curvedArrow'},
    {source:'2',target:'1',id:'3',label:'5',type: 'curvedArrow'},
    {source:'3',target:'5',id:'4',label:'1',type: 'curvedArrow'},
    {source:'3',target:'4',id:'5',label:'4',type: 'curvedArrow'},
    {source:'4',target:'3',id:'6',label:'3',type: 'curvedArrow'},
    {source:'5',target:'4',id:'7',label:'3',type: 'curvedArrow'}
  ]
}