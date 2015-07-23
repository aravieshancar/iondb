/*
 * linearhash.c
 *
 *  Created on: Apr 7, 2015
 *      Author: workstation
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "./../../../CuTest.h"
#include "./../../../../dictionary/linearhash/file_ll.h"

/**
 * Creates an empty test linked list file as a starting point
 * @param linked_list_file
 * 			Struct for ll
 */
void
create_test_linked_list(
	ll_file_t 		*linked_list_file,
	int 			id
	)
{
	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;
	fll_create(linked_list_file, fll_compare, key_type_numeric_signed, record.key_size,
	        record.value_size, 0, id);
}

/**
 * closes and clean up linked list file
 * @param linked_list_file
 * 			Struct for ll
 */
void
remove_linked_list(
	ll_file_t		*linked_list_file)
{

	fclose(linked_list_file->file);
	remove(linked_list_file->file_name);
	free(linked_list_file->file_name);
}

/**
@brief 		Tests for creation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_initialize(
	CuTest		*tc
)
{
	int id = 9;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);
	char filename[20];
	sprintf(filename,"%i_%i.ovf",id,0);
	//valid correct map settings
	CuAssertTrue(tc, 0	 							== strcmp(linked_list_file.file_name,filename));
	//check that the first node is actually the head
	char * node;
	//when reading raw, allocate entire node
	node = (char *)malloc(sizeof(char)*(linked_list_file.node_size));

	/** Reset the position to the start of the list, otherwise you will get the node after this.
	 * This is a special case for testing */
	linked_list_file.current = HEAD_NODE;
	fll_get(&linked_list_file,(ll_file_node_t *)node);
	//This should find the head node
	CuAssertTrue(tc, END_OF_LIST	 					== ((ll_file_node_t*)node)->next);

	//cleanup node
	free(node);
	remove_linked_list(&linked_list_file);
}

/**
@brief 		Tests for creation of linked list nodes

@param 		tc
				CuTest
 */
void
test_file_linked_list_node_creation(
	CuTest		*tc
)
{
	int id = 0;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file,id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int key = 10;
	char * value = "value";

	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_file_node_t * ll_node = (ll_file_node_t *)node;

	//validate node that is created
	CuAssertTrue(tc, END_OF_LIST	 				== ll_node->next);
	CuAssertTrue(tc, key 							== *(int*)ll_node->data);
	CuAssertTrue(tc, 0	 							== strcmp((char *)(ll_node->data+record.key_size),value));

	ll_file_node_t * node2;
	key = 11;

	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node2);
	ll_file_node_t * ll_node2 = (ll_file_node_t *)node2;

	//validate node that is created
	CuAssertTrue(tc, END_OF_LIST	 				== ll_node2->next);
	CuAssertTrue(tc, key 							== *(int*)ll_node2->data);
	CuAssertTrue(tc, 0	 							== strcmp((char *)(ll_node2->data+record.key_size),value));

	//compare nodes
	CuAssertTrue(tc, -1	 							== linked_list_file.compare(&linked_list_file,ll_node,ll_node2));
	CuAssertTrue(tc, 1	 							== linked_list_file.compare(&linked_list_file,ll_node2,ll_node));
	CuAssertTrue(tc, 0 								== linked_list_file.compare(&linked_list_file,ll_node,ll_node));

	//cleanup node
	free(node);
	free(node2);
	remove_linked_list(&linked_list_file);
}
/**
@brief 		Tests for creation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_insert(
	CuTest		*tc
)
{
	int id = 1;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int key = 10;
	char * value = "value";

	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_file_node_t * ll_node = (ll_file_node_t *)node;

	//validate node that is created
	CuAssertTrue(tc, END_OF_LIST	 				== ll_node->next);
	CuAssertTrue(tc, key 							== *(int*)ll_node->data);
	CuAssertTrue(tc, 0	 							== strcmp((char *)(ll_node->data+record.key_size),value));

	fll_insert(&linked_list_file,ll_node);
	free(node);

	key = 11;
	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_node = (ll_file_node_t *)node;
	fll_insert(&linked_list_file,ll_node);
	free(node);

	key = 8;
	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_node = (ll_file_node_t *)node;
	fll_insert(&linked_list_file,ll_node);
	free(node);


	key = 50;
	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_node = (ll_file_node_t *)node;
	fll_insert(&linked_list_file,ll_node);
	free(node);

	key = 13;
	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_node = (ll_file_node_t *)node;
	fll_insert(&linked_list_file,ll_node);
	free(node);

	/** Read file directly to ensure that it is working*/
	rewind(linked_list_file.file);

	ll_file_node_t * read_node;
	read_node = (ll_file_node_t *)malloc(linked_list_file.node_size);		/** Allocate space for node */
	/** Each record is 18 bytes.  First Record is head node and does not contain a key */

	//this is the head node
	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	int next_node = 1;

	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, 54 										== read_node->next);


	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	next_node = 2;
	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, 36	 						 				== read_node->next);
	CuAssertTrue(tc, 10 										== *(int*)read_node->data);

	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	next_node = 3;
	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, 90	 						 				== read_node->next);
	CuAssertTrue(tc, 11 										== *(int*)read_node->data);

	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	next_node = 4;
	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, 18	 						 				== read_node->next);
	CuAssertTrue(tc, 8 											== *(int*)read_node->data);

	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	next_node = 5;
	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, END_OF_LIST	 						 	== read_node->next);
	CuAssertTrue(tc, 50 										== *(int*)read_node->data);

	fread(read_node,linked_list_file.node_size,1,linked_list_file.file);
	next_node = 6;
	CuAssertTrue(tc, linked_list_file.node_size * next_node		== ftell(linked_list_file.file));
	CuAssertTrue(tc, 72	 						 				== read_node->next);
	CuAssertTrue(tc, 13 										== *(int*)read_node->data);

	free(read_node);
	remove_linked_list(&linked_list_file);
}

/**
@brief 		Tests for next operation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_next(
	CuTest		*tc
)
{
	int id = 2;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int idx;
	char * value = "value";
	int key_array[] = {10,11,8,50,13};

	for (idx=0;idx<5;idx++)
	{
		fll_create_node(&linked_list_file, &record, (ion_key_t)&key_array[idx], (ion_value_t)value, &node);
		ll_file_node_t * ll_node = (ll_file_node_t *)node;
		fll_insert(&linked_list_file,ll_node);
		free(node);
	}

	/**Reset iterator */
	fll_reset(&linked_list_file);

	int key_array_ans[] = {8,10,11,13,50};
	idx = 0;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	//cleanup node
	free(node);
	remove_linked_list(&linked_list_file);
}


/**
@brief 		Tests for next operation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_find(
	CuTest		*tc
)
{
	int id = 3;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int idx;
	char * value = "value";
	int key_array[] = {10,11,8,50,13};

	for (idx=0;idx<5;idx++)
	{
		fll_create_node(&linked_list_file, &record, (ion_key_t)&key_array[idx], (ion_value_t)value, &node);
		ll_file_node_t * ll_node = (ll_file_node_t *)node;
		fll_insert(&linked_list_file,ll_node);
		free(node);
	}

	int key_to_find = 13;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	CuAssertTrue(tc, err_ok							== fll_find(&linked_list_file,(ion_key_t)&key_to_find,node));
	CuAssertTrue(tc, key_to_find					== *(int*)node->data);
	free(node);

	key_to_find = 10;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	CuAssertTrue(tc, err_ok							== fll_find(&linked_list_file,(ion_key_t)&key_to_find,node));
	CuAssertTrue(tc, key_to_find					== *(int*)node->data);
	free(node);

	key_to_find = 11;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	CuAssertTrue(tc, err_ok							== fll_find(&linked_list_file,(ion_key_t)&key_to_find,node));
	CuAssertTrue(tc, key_to_find					== *(int*)node->data);
	free(node);

	key_to_find = 50;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	CuAssertTrue(tc, err_ok							== fll_find(&linked_list_file,(ion_key_t)&key_to_find,node));
	CuAssertTrue(tc, key_to_find					== *(int*)node->data);
	free(node);

	key_to_find = 60;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	CuAssertTrue(tc, err_item_not_found				== fll_find(&linked_list_file,(ion_key_t)&key_to_find,node));
	free(node);
	//cleanup node
	remove_linked_list(&linked_list_file);
}

/**
@brief 		Tests for delete operation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_delete(
	CuTest		*tc
)
{
	int id = 4;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int idx;
	char * value = "value";
	int key_array[] = {10,11,8,50,13};


	for (idx=0;idx<5;idx++)
	{
		fll_create_node(&linked_list_file, &record, (ion_key_t)&key_array[idx], (ion_value_t)value, &node);
		ll_file_node_t * ll_node = (ll_file_node_t *)node;
		fll_insert(&linked_list_file,ll_node);
		free(node);
	}

	int delete_key = 8;
	fll_delete(&linked_list_file, (ion_key_t)&delete_key);

	fll_reset(&linked_list_file);								/** reset iterator /*/
	int key_array_ans[] = {10,11,13,50};
	idx = 0;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	delete_key = 13;
	fll_delete(&linked_list_file, (ion_key_t)&delete_key);
	fll_reset(&linked_list_file);
	int key_array_ans_2[] = {10,11,50};
	idx = 0;
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans_2[idx++]						== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	delete_key = 11;
	fll_delete(&linked_list_file, (ion_key_t)&delete_key);

	fll_reset(&linked_list_file);
	int key_array_ans_3[] = {10,50};
	idx = 0;
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans_3[idx++]						== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	delete_key = 50;
	fll_delete(&linked_list_file, (ion_key_t)&delete_key);

	fll_reset(&linked_list_file);
	int key_array_ans_4[] = {10};
	idx = 0;
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans_4[idx++]						== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	delete_key = 10;
	fll_delete(&linked_list_file, (ion_key_t)&delete_key);
	fll_reset(&linked_list_file);
	int key_array_ans_5[] = {};
	idx = 0;
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans_5[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	//cleanup node
	free(node);
	remove_linked_list(&linked_list_file);
}

/**
brief 		Tests for remove operation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_remove (
	CuTest		*tc
)
{
	int id = 5;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int idx;
	char * value = "value";
	int key_array[] = {10,11,8,50,13};

	for (idx=0;idx<5;idx++)
	{
		fll_create_node(&linked_list_file, &record, (ion_key_t)&key_array[idx], (ion_value_t)value, &node);
		ll_file_node_t * ll_node = (ll_file_node_t *)node;
		fll_insert(&linked_list_file,ll_node);
		free(node);
	}

	fll_reset(&linked_list_file);								/** reset iterator /*/
	int key_array_ans[] = {8,10,11,13,50};
	idx = 0;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));
	free(node);

	fll_reset(&linked_list_file);								/** reset iterator */
	idx = 0;
	node = (ll_file_node_t *)malloc(linked_list_file.node_size);
	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
		CuAssertTrue(tc, err_ok									== fll_remove(&linked_list_file));
		CuAssertTrue(tc, err_illegal_state						== fll_remove(&linked_list_file));
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	//cleanup node
	free(node);
	remove_linked_list(&linked_list_file);
}


/**
brief 		Tests for remove operation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_remove2 (
	CuTest		*tc
)
{
	int id = 6;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int idx;
	char * value = "value";
	int key_array[] = {10,11,8,50,13};

	for (idx=0;idx<5;idx++)
	{
		fll_create_node(&linked_list_file, &record, (ion_key_t)&key_array[idx], (ion_value_t)value, &node);
		ll_file_node_t * ll_node = (ll_file_node_t *)node;
		fll_insert(&linked_list_file,ll_node);
		free(node);
	}

	node = (ll_file_node_t *)malloc(linked_list_file.node_size);

	fll_reset(&linked_list_file);								/** reset iterator */
	int key_array_ans[] = {8,10,11,13,50};

	CuAssertTrue(tc, err_illegal_state							== fll_remove(&linked_list_file));

	idx = 0;
	CuAssertTrue(tc, err_ok										== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, key_array_ans[idx++]						== *(int*)node->data);
	CuAssertTrue(tc, err_ok										== fll_remove(&linked_list_file));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/

	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/
	idx = 1;
	CuAssertTrue(tc,err_ok										== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, key_array_ans[idx++]						== *(int*)node->data);
	CuAssertTrue(tc, err_ok										== fll_remove(&linked_list_file));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/

	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/
	idx = 2;
	CuAssertTrue(tc,err_ok										== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, key_array_ans[idx++]						== *(int*)node->data);
	CuAssertTrue(tc, err_ok										== fll_remove(&linked_list_file));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/

	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/
	idx = 3;
	CuAssertTrue(tc,err_ok										== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, key_array_ans[idx++]						== *(int*)node->data);
	CuAssertTrue(tc, err_ok										== fll_remove(&linked_list_file));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/

	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/
	idx = 4;
	CuAssertTrue(tc,err_ok										== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, key_array_ans[idx++]						== *(int*)node->data);
	CuAssertTrue(tc, err_ok										== fll_remove(&linked_list_file));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/

	while (fll_next(&linked_list_file,node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,node));

	fll_reset(&linked_list_file);								/** reset iterator and check list*/
	CuAssertTrue(tc,err_item_not_found							== fll_next(&linked_list_file,node));
	CuAssertTrue(tc, err_illegal_state							== fll_remove(&linked_list_file));


	//cleanup node
	free(node);
	remove_linked_list(&linked_list_file);
}

/**
@brief 		Tests for creation of linked list

@param 		tc
				CuTest
 */
void
test_file_linked_list_reopen(
	CuTest		*tc
)
{
	int id = 7;
	//create linked list file struct
	ll_file_t linked_list_file;
	create_test_linked_list(&linked_list_file, id);

	record_info_t record;
	record.key_size = 4;
	record.value_size = 10;

	//check that the first node is actually the head
	ll_file_node_t * node;
	int key = 10;
	char * value = "value";

	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_file_node_t * ll_node = (ll_file_node_t *)node;

	//validate node that is created
	CuAssertTrue(tc, END_OF_LIST	 				== ll_node->next);
	CuAssertTrue(tc, key 							== *(int*)ll_node->data);
	CuAssertTrue(tc, 0	 							== strcmp((char *)(ll_node->data+record.key_size),value));

	fll_insert(&linked_list_file,ll_node);
	free(node);

	key = 11;
	fll_create_node(&linked_list_file, &record, (ion_key_t)&key, (ion_value_t)value, &node);
	ll_node = (ll_file_node_t *)node;
	fll_insert(&linked_list_file,ll_node);
	free(node);

	fclose(linked_list_file.file);
	free(linked_list_file.file_name);				/** and free the name too as this is reallocated when the file is opened */

	if (fll_open(&linked_list_file, fll_compare, key_type_numeric_signed, record.key_size,
		        record.value_size, 0, id) == err_item_not_found)
	{
		fll_create(&linked_list_file, fll_compare, key_type_numeric_signed, record.key_size,
		        record.value_size, 0, id);
	}

	ll_file_node_t * read_node;
	read_node = (ll_file_node_t *)malloc(linked_list_file.node_size);

	int key_array_ans[] = {10,11};
	int idx = 0;

	while (fll_next(&linked_list_file,read_node) != err_item_not_found)
	{
		CuAssertTrue(tc, key_array_ans[idx++]					== *(int*)read_node->data);
	}
	CuAssertTrue(tc, err_item_not_found							== fll_next(&linked_list_file,read_node));

	free(read_node);
	remove_linked_list(&linked_list_file);

}

CuSuite*
file_linked_list_getsuite()
{
	CuSuite *suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, test_file_linked_list_initialize);
	SUITE_ADD_TEST(suite, test_file_linked_list_node_creation);
	SUITE_ADD_TEST(suite, test_file_linked_list_insert);
	SUITE_ADD_TEST(suite, test_file_linked_list_next);
	SUITE_ADD_TEST(suite, test_file_linked_list_find);
	SUITE_ADD_TEST(suite, test_file_linked_list_delete);
	SUITE_ADD_TEST(suite, test_file_linked_list_remove);
	SUITE_ADD_TEST(suite, test_file_linked_list_remove2);
	SUITE_ADD_TEST(suite, test_file_linked_list_reopen);
	return suite;
}


void
runalltests_file_linked_list()
{
	CuString	*output	= CuStringNew();
	CuSuite		*suite	= file_linked_list_getsuite();

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);

	CuSuiteDelete(suite);
	CuStringDelete(output);
}