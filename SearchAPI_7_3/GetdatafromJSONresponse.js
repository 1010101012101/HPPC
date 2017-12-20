function getProducts(stringData)
{
var data = JSON.parse(stringData);
var value = data.ProductsCount; // Specific to the response
return value;
} 


function getRecommendedType(stringData)
{
var rectype;
var data = JSON.parse(stringData);
var value = data.Products.length;// Specific to the response
if (value >= 1)
{
	rectype=data.Products[0].RecommendedType;
}
else
{
rectype=-1;
}
	
return rectype;
} 

function getNoofProducts(stringData)
{
var data = JSON.parse(stringData);
var value2 = data.Products.length;  // Specific to the response
return value2;
} 

function APItimeout(stringData)
{
var data = JSON.parse(stringData);
var value2 = data.Errors.length;  // Specific to the response
return value2;
} 

function APItimeoutcode(stringData)
{
var data = JSON.parse(stringData);
var value2 = data.Errors[0].Code;  // Specific to the response
return value2;
} 
function APItimeoutmessage(stringData)
{
var data = JSON.parse(stringData);
var value2 = data.Errors[0].Message;  // Specific to the response
return value2;
} 