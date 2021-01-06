/* Description:
 * 	This test checks that the size of the buffer doubles once the contents fills more than 50%
 * Author:
 * 	Benjamin Mordaunt
 * Date:
 * 	06/01/2020
 */

#include <check.h>
#include "extbuffer.h"

START_TEST (test_buffer_expansion)
{
	char data = 'a';

	// Create a new buffer, with a resize ratio of 50%.
	ceb_buffer_t buf = { 0 }; // Cannot set .rsz_ratio here as overwritten by ceb_init_buffer
	
	ceb_init_buffer(&buf, 10);
	
	buf.rsz_ratio = 50;

	// Add 4 chars to the buffer and ensure that the size remains the same.
	for(int i = 0; i < 4; i++) {
		CEXTPUT(&buf, data); 
	}

	ck_assert_int_eq(buf.sz, 10);

	// Add 2 more chars and ensure that the size is doubled.
	for(int i = 0; i < 2; i++) {
		CEXTPUT(&buf, data);
	}

	ck_assert_int_eq(buf.sz, 20);

	// Free the buffer.
	ceb_free_buffer(&buf);
}
END_TEST /* test_buffer_expansion */

Suite *suite() {
	Suite *s;
	TCase *tc_core;

	s = suite_create("Buffer Behaviour");

	tc_core = tcase_create("Expansion");

	tcase_add_test(tc_core, test_buffer_expansion);
	suite_add_tcase(s, tc_core);

	return s;
}

int main() {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed != 0);
}
