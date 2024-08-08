class Config {
    int max_elements;
    int num_iterations;
    int random_bound;
    QString file_path;
public:
    Config(int max_elements, int num_iterations, int random_bound)
            : max_elements(max_elements), num_iterations(num_iterations), random_bound(random_bound) {}
    Config(){}

    int getMaxElements() const {
        return max_elements;
    }
    int getNumIterations() const {
        return num_iterations;
    }
    int getRandomBound() const {
        return random_bound;
    }
    QString getFilePath(){
        return file_path;
    }
    void setMaxElements(int maxElements) {
        max_elements = maxElements;
    }
    void setNumIterations(int numIterations) {
        num_iterations = numIterations;
    }
    void setRandomBound(int randomBound) {
        random_bound = randomBound;
    }
    void setFilePath(QString filePath){
        file_path = filePath;
    }

};
