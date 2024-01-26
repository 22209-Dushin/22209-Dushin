class configFailure : public std::exception {
public:
    configFailure(const char* massage) {
        m = massage;
    }
    configFailure() {
        m = nullptr; 
    }
    const char* what() const noexcept {
        if (m == nullptr)
            return "Bad configuration file";
        else 
            return m;
    }
private:
    const char* m;
};
