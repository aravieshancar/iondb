/******************************************************************************/
/**
@file		slhandler.h
@author		Kris Wallperington
@brief		Handler liaison between dictionary API and skiplist implementation
*/
/******************************************************************************/
#ifndef SLHANDLER_H
#define SLHANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./../dicttypes.h"
#include "./../dictionary.h"
#include "./../../kv_system.h"
#include "slstore.h"

/**
@brief 		Registers a skiplist handler to a dictionary instance.

@details 	Binds each unique skiplist function to the generic dictionary
			interface. Only needs to be called once when the skiplist is
			initialized.

@param 		handler
				An instance of a dictionary handler that is to be bound.
				It is assumed @p handler is initialized by the user.
@return 	Status of initialization.
 */
err_t
sldict_init(
	dictionary_handler_t 	*handler
);

/**
@brief 		Inserts a @p key and @p value pair into the dictionary.

@param 		dictionary
				The dictionary instance to insert the value into.
@param 		key
				The key to use.
@param 		value
				The value to use.
@return 	Status of insertion.
 */
err_t
sldict_insert(
	dictionary_t 	*dictionary,
	ion_key_t 		key,
	ion_value_t 	value
);

/**
@brief 		Queries a dictionary instance for a given @p key and returns the
			corresponding @p value.

@details 	Queries a dictionary instance for a given @p key and returns the
			@p value within, copied into the pointer provided by the user.
			Assumption is that the pointer is passed unallocated, for this
			function to allocate. The onus is then on the user to free the
			given memory.

@param 		dictionary
				The instance of the dictionary to query
@param 		key
				The key to search for.
@param 		value
				A pointer used to hold the returned value from the query.
				This function will malloc the memory, and it is up to the
				consumer to free the memory once they're done with it.
@return 	Status of query.
 */
err_t
sldict_query(
	dictionary_t 	*dictionary,
	ion_key_t 		key,
	ion_value_t 	*value
);

/**
@brief 		Creates an instance of a dictionary.

@details 	Creates an instance of a dictionary given a @p key_size and
			@p value_size, in bytes as well as the @p dictionary_size, which
			is the maximum number of levels in the skiplist. By nature of the
			structure, the maximum number of elements is bounded only by memory
			use.

@param 		key_size
				Size of the key in bytes.
@param 		value_size
				Size of the value in bytes.
@param 		handler
				Handler to be bound to the dictionary instance being created.
				Assumption is that the handler has been initialized prior.
@param 		dictionary
				Pointer in which the created dictionary instance is to be
				stored. Assumption is that it has been properly allocated by
				the user.
@return 	Status of creation.
 */
err_t
sldict_create_dictionary(
	int 					key_size,
	int 					value_size,
	int 					dictionary_size,
	dictionary_handler_t 	*handler,
	dictionary_t 			*dictionary
);

/**
@brief 		Deletes the @p key and associated value from the given dictionary
			instance.

@param 		dictionary
				The instance of the dictionary to delete from.
@param 		key
				The key to be deleted.
@return 	Status of deletion.
 */
err_t
sldict_delete(
	dictionary_t 	*dictionary,
	ion_key_t 		key
);

/**
@brief 		Deletes an instance of a dictionary and its associated data.

@param 		dictionary
				The instance of the dictionary to be deleted.
@return 	Status of dictionary deletion.
 */
err_t
sldict_delete_dictionary(
	dictionary_t 	*dictionary
);

/**
@brief 		Updates the value stored at a given key.

@details 	Updates the value for a given @p key. If the key doesn't exist,
			the key value pair will be added as if it was an insert.

@param 		dictionary
				The instance of the dictionary to be updated.
@param 		key
				The key that is to be updated.
@param 		value
				The new value to be used.
@return Status of update.
 */
err_t
sldict_update(
	dictionary_t 	*dictionary,
	ion_key_t 		key,
	ion_value_t 	value
);

#ifdef __cplusplus
}
#endif

#endif /* SLHANDLER_H */