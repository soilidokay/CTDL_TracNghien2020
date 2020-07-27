#ifndef PROFILE_USER_H
#define PROFILE_USER_H

#include <iostream>

class ProfileUser {
public:
	std::string USerId;
	static ProfileUser* Istance;
	static ProfileUser* getInstance() {
		if (ProfileUser::Istance == NULL) {
			ProfileUser::Istance = new ProfileUser();
		}
		return ProfileUser::Istance;
	}
};
ProfileUser* ProfileUser::Istance = NULL;
#endif // !PROFILE_USER_H
