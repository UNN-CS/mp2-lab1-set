# include  " tset.h "

# include  < gtest.h >

TEST(TSet, can_get_max_power_set)
{
	const  int size = 5;
	TSet set(taille);

	EXPECT_EQ(taille, définition.GetMaxPower());
}

TEST(TSet, can_insert_non_existing_element)
{
	const  int size = 5, k = 3;
	TSet set(taille);
	ensemble.Inselem(k);

	EXPECT_NE(défini.IsMember(k), 0);
}

TEST(TSet, can_insert_existing_element)
{
	const  int size = 5;
	const  int k = 3;
	TSet set(taille);
	ensemble.Inselem(k);
	ensemble.Inselem(k);

	EXPECT_NE(défini.IsMember(k), 0);
}

TEST(TSet, can_delete_non_existing_element)
{
	const  int size = 5, k = 3;
	TSet set(taille);
	ensemble.DelElem(k);

	EXPECT_EQ(défini.IsMember(k), 0);
}

TEST(TSet, can_delete_existing_element)
{
	const  int size = 5, k = 3;
	TSet set(taille);

	ensemble.Inselem(k);
	EXPECT_GT(set.IsMember(k), 0);

	ensemble.DelElem(k);
	EXPECT_EQ(défini.IsMember(k), 0);
}

TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
	const  int taille1 = 4, taille2 = 6;
	TSet set1(taille1), set2(taille2);

	EXPECT_EQ(1, set1!= Set2);
}

TEST(TSet, compare_two_equal_sets)
{
	const  int size = 4;
	TSet set1(taille), set2(taille);
	// set1 = set2 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2.InsElem(1);
	set2.InsElem(3);

	EXPECT_EQ(set1, set2);
}

TEST(TSet, compare_two_non_equal_sets)
{
	const  int size = 4;
	TSet set1(taille), set2(taille);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	// set2 = {1, 2}
	set2.InsElem(1);
	set2.Inselem(2);

	EXPECT_EQ(1, set1!= Set2);
}

TEST(TSet, can_assign_set_of_equal_size)
{
	const  int size = 4;
	TSet set1(taille), set2(taille);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_greater_size)
{
	const  int taille1 = 4, taille2 = 6;
	TSet set1(taille1), set2(taille2);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_less_size)
{
	const  int taille1 = 6, taille2 = 4;
	TSet set1(taille1), set2(taille2);
	// set1 = {1, 3, 5}
	set1.InsElem(1);
	set1.InsElem(3);
	set1.InsElem(5);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
	const  int size = 4;
	const  int k = 3;
	TSet set(taille), updatedSet(taille);
	ensemble.Inselem(0);
	ensemble.Inselem(2);
	updatedSet = set + k;

	EXPECT_NE(0, updatedSet.IsMember(k));
}

ESSAI(TEST, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
	const  int size = 4;
	const  int k = 6;
	TSet set(taille), updatedSet(taille);
	ensemble.Inselem(0);
	ensemble.Inselem(2);

	ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(TSet, can_insert_existing_element_using_plus_operator)
{
	const  int size = 4;
	const  int k = 3;
	TSet set(taille), updatedSet(taille);
	ensemble.Inselem(0);
	ensemble.Inselem(k);
	updatedSet = set + k;

	EXPECT_NE(0, défini.IsMember(k));
}

TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
	const  int size = 5;
	TSet set1(taille), set2(taille), set3(taille);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set3 = set1 + set2;

	EXPECT_EQ(size, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_equal_size)
{
	const  int size = 5;
	TSet set1(taille), set2(taille), set3(taille), expSet(taille);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set3 = set1 + set2;
	// expSet = {0, 1, 2, 4}
	expSet.Inselem(0);
	expSet.InsElem(1);
	expSet.Inselem(2);
	expSet.InsElem(4);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_size_changes_de_la_combinaison_des_deux_sets_du_signal_equal)
{
	const  int taille1 = 5, taille2 = 7;
	TSet set1(taille1), set2(taille2), set3(taille1);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set3 = set1 + set2;

	EXPECT_EQ(size2, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
	const  int taille1 = 5, taille2 = 7;
	TSet set1(taille1), set2(taille2), set3(taille1), expSet(taille2);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2, 6}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set2.InsElem(6);
	set3 = set1 + set2;
	// expSet = {0, 1, 2, 4, 6}
	expSet.Inselem(0);
	expSet.InsElem(1);
	expSet.Inselem(2);
	expSet.InsElem(4);
	expSet.InsElem(6);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_equal_size)
{
	const  int size = 5;
	TSet set1(taille), set2(taille), set3(taille), expSet(taille);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set3 = set1 * set2;
	// expSet = {1, 2}
	expSet.InsElem(1);
	expSet.Inselem(2);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
	const  int taille1 = 5, taille2 = 7;
	TSet set1(taille1), set2(taille2), set3(taille1), expSet(taille2);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.Inselem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2, 4, 6}
	set2.Inselem(0);
	set2.InsElem(1);
	set2.Inselem(2);
	set2.InsElem(4);
	set2.InsElem(6);
	set3 = set1 * set2;
	// expSet = {1, 2, 4}
	expSet.InsElem(1);
	expSet.Inselem(2);
	expSet.InsElem(4);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_negation_operator)
{
	const  int size = 4;
	TSet set(taille), set1(taille), expSet(taille);
	// set1 = {1, 3}
	ensemble.InsElem(1);
	ensemble.InsElem(3);
	set1 = ~set;
	// expSet = {0, 2}
	expSet.Inselem(0);
	expSet.Inselem(2);

	EXPECT_EQ(expSet, set1);
}

TEST(TSet, my_test_no_name_number_one)
{
	const  int size = 2;
	TSet set(taille);
	// set = {0}
	ensemble.Inselem(0);

	EXPECT_EQ(1, set.IsMember(0));
}

TEST(TSet, throw_in_assignment_operator)
{
	const  int size = 3;
	TSet set(taille);

	EXPECT_ANY_THROW(set = set);
}
