PickupEvent:DRIVINGSCHOOL(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_KEYPRESS:
		{
			if (HasLicense(playerID, "Car") && HasLicense(playerID, "Trucker") && HasLicense(playerID, "Bike"))
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:593("You already have all driving licenses you can earn at this driving school!"));
			}
			else
			{
				ShowDialog:DrivingSchool(playerID);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:DRIVINGSCHOOL(pickupID)
{
	return 1239;
}