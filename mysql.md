## mysql按天，小时，半小时，N分钟，分钟进行数据分组统计

https://blog.csdn.net/u010946448/article/details/83752984

```mysql
SELECT
	DATE_FORMAT( ttimestamp, '%Y-%m-%d %H:%i:00' ) AS time,
	AVG( test_result ) AS test_result_avg 
FROM
	testlamda 
WHERE
	ttimestamp >= "2020-09-08 10:45:00"  
GROUP BY
	time 
ORDER BY
	time;
  ```
