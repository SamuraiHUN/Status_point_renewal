search this function:

ACMD(do_stat)


and change to:

ACMD(do_stat)
{
	char arg1[256], arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || !*arg2)
		return;

	if (ch->IsPolymorphed())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("µĐ°© Áßżˇ´Â ´É·ÂŔ» żĂ¸± Ľö ľř˝Ŕ´Ď´Ů."));
		return;
	}

	if (ch->GetPoint(POINT_STAT) <= 0)
		return;

	BYTE idx = 0;

	if (!strcmp(arg1, "st"))
		idx = POINT_ST;
	else if (!strcmp(arg1, "dx"))
		idx = POINT_DX;
	else if (!strcmp(arg1, "ht"))
		idx = POINT_HT;
	else if (!strcmp(arg1, "iq"))
		idx = POINT_IQ;
	else
		return;

	if (ch->GetRealPoint(idx) >= MAX_STAT)
		return;
	int point_incr = 1;
	int deline = MAX_STAT - ch->GetRealPoint(idx);
	str_to_number(point_incr, arg2);
	point_incr = MIN(point_incr, deline);

	if (point_incr <= 0)
		return;
	else if (point_incr > ch->GetPoint(POINT_STAT))
		point_incr = ch->GetPoint(POINT_STAT);
	
	ch->SetRealPoint(idx, ch->GetRealPoint(idx) + point_incr);
	ch->SetPoint(idx, ch->GetPoint(idx) + point_incr);
	ch->ComputePoints();
	ch->PointChange(idx, 0);

	if (idx == POINT_IQ)
	{
		ch->PointChange(POINT_MAX_HP, 0);
	}
	else if (idx == POINT_HT)
	{
		ch->PointChange(POINT_MAX_SP, 0);
	}

	ch->PointChange(POINT_STAT, -point_incr);
	ch->ComputePoints();
}