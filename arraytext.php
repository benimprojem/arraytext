<?php
/*
 Array dan texte örnek 
 bu şekilde veri iletimi json dan daha küçük boyutlarda veri taşınabilir.

*/
$categoryid = 2;
	$start = 0;
	$limit = 1000;
	$sql="SELECT * FROM `products` WHERE categoryid = ? ORDER by name LIMIT ?, ?";
	$context['productlist'] = prepared_select($conn, $sql, [$categoryid, $start, $limit])->fetch_all(MYSQLI_ASSOC);
	echo'#'.$categoryid.' <br>';
	$i = 0;
	foreach ($context['productlist'] as $row){
		$i != 0 ? $v=',<br>' : $v='';
		echo''.$v.'{['.$row['productid'].','.$row['name'].','.$row['productcode'].','.$row['info'].',['.$row['price'].','.$row['price2'].','.$row['price3'].'],'.$row['stock'].',['.$row['image'].']]}';
		$i++;
	}
