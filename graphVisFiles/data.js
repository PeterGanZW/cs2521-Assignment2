g = {
  nodes: [
    {id:'0',label:'0',x:0.300000,y:0.000000, size:0.2, color: getColor(1.000000,gradient)},
    {id:'1',label:'1',x:0.092705,y:0.285317, size:0.2, color: getColor(1.000000,gradient)},
    {id:'2',label:'2',x:-0.242705,y:0.176336, size:0.2, color: getColor(1.000000,gradient)},
    {id:'3',label:'3',x:-0.242705,y:-0.176336, size:0.2, color: getColor(1.000000,gradient)},
    {id:'4',label:'4',x:0.092705,y:-0.285317, size:0.2, color: getColor(1.000000,gradient)}
  ],
  edges: [
    {source:'0',target:'4',id:'0',label:'2',type: 'curvedArrow'},
    {source:'1',target:'2',id:'1',label:'1',type: 'curvedArrow'},
    {source:'1',target:'4',id:'2',label:'2',type: 'curvedArrow'},
    {source:'1',target:'0',id:'3',label:'1',type: 'curvedArrow'},
    {source:'2',target:'1',id:'4',label:'10',type: 'curvedArrow'},
    {source:'2',target:'3',id:'5',label:'1',type: 'curvedArrow'},
    {source:'3',target:'2',id:'6',label:'6',type: 'curvedArrow'},
    {source:'3',target:'4',id:'7',label:'1',type: 'curvedArrow'},
    {source:'3',target:'1',id:'8',label:'5',type: 'curvedArrow'},
    {source:'4',target:'2',id:'9',label:'60',type: 'curvedArrow'}
  ]
}