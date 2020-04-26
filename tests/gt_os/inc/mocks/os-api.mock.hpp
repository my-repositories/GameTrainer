#ifndef GAMETRAINER_OS_API_MOCK_HPP
#define GAMETRAINER_OS_API_MOCK_HPP

class OsApiMock : public gt::os::OsApi {
public:
    MOCK_CONST_METHOD1(getAsyncKeyState, SHORT(int));
};

#endif // GAMETRAINER_OS_API_MOCK_HPP
