# Notice of multi_index
* primary key cannot be defined from multiple columns. Only one columns can be a primary key.
	+ if want to implement it, use secondary index.
```
eosio::multi_index< N( orders ), limit_order, 
			  indexed_by< N( byexp ),   const_mem_fun< limit_order, uint64_t, &limit_order::get_expiration> >,
			  indexed_by< N( byprice ), const_mem_fun< limit_order, uint128_t, &limit_order::get_price> >
			> orders( N( limitorders ), N( limitorders ) );	
```
* eosio::multi_index< N(orders), limit_order, 
	+ N(orders) is name of the multi index table
	+ limit_orders is the data to be sotred in the table.
* indexed_by< N(byexp), const_mem_fun<ilmit_order, uint64_t, &limit_order::get_expiration> >,
	+ It is definition of a way the orders that multi index table can be indexed.
	+ N(byexp) is the name of this index.
	+ const_mem_fun indicates the data type being retrieved 
		- the type of variable being sorted by limit_order.
		- uint64_t is the function that will be used get the variable which get_expiration
* indexed_by< N(byprice), const_mem_fun< limit_order, uint128_t, &limit_order::get_price> >
	+ the definition of a way the orders that multi index table can be indexed.
	+ N(byprice) is the name of this index.
	+ const_mem_fun indicates the data type being retrieved(searched)
		- the other is same of above
* orders( N(limitorders), N(limitorders) );
	+ orders is multi index table

## Modify a table
table cannot be directly modified. if you want to do this, follow this step.

1. Create another table
2. Implement migration function
3. After migration, you may delete records of the old table
```
step1
struct limit_order{
	uint64_t id;
	uint128_t price;
	uint64_t id;
	account owner;
	
	auto primary_key() const { return id; }
};
typedef eosio::multi_index< N(orders), limit_order> _limit_order;
struct limit_order2 { // new table
	uint64_t id;
	uint128_t price;
	uint64_t expiration;
	account_name owner;
	asset byeos;	// added column
	
	auto primary_key() const {	return id; }
};
typedef eosio::multi_index<N(orders2), limit_order2> _limit_order2;

step2.
void sth::migrate(){
	require_auth(_self);

	_limit_order old_table(_self, _self);
	_limit_order2 new_table(_self, _self);

	auto itr = old_table.begin();
	whileiter != old_table.end()){
		new_table.emplace(_self, [&](auto& o){
			o.id = itr.id;
			o.price = itr.price;
			o.expiration = itr.expiration;
			o.owner = itr.owner;
			o.byeos = itr.price / 3;	// implement yourself
		});
	}

step3. delete old table
}
```
