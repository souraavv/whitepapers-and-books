

- Topology
- StreamBuilder


- KafkaStreamAPI (Functional/Lambda)
- filter
- filterNot 

- Map 
    - Both value and keys
    `.map((key, value) -> KeyValue.pair(key.toUpperCase(), value.toUpperCase());`

- MapValues
    ONly values
    `.mapValues((readOnlyKey, value) -> value.toUpperCase())`

- FlatMap

    ```
    greetingsStream
            .filter((key, value) -> value.length() > 5) 
            .flatMap((key, value) -> {
                var newValue = Arrays.asList(value.split(" "));
                var keyValueList = newValue
                        .stream()
                        .map(t -> KeyValue.pair(key.toUpperCase(), t))
                        .collect(Collectors.list());
                return keyValueList;
            });
    ```

- FlatMapValues

    ```
    var upperCaseStream = greetingsStream
            .filter((key, value) -> value.length() > 5)
            .filterMapValue((readOnlyKey, value) -> {
                var newValue = Arrays.asList(value.split(" ");
                return newValue;
            });

    ```

- peek
    
    ```
    var modifiedStream = greetingsStream
            .filter((key, value) -> value.length() > 5)
            .peek((key, value) -> {
                key.toUpperCase(); <-- No changes
                log.info("After filter: key: {}, value: {}", key, value);
            })
            .map...


    ```

    - Benefit: Debugging (filter -(debug via Peek)-> Map -> ..debug..-> ..)
    - No changes to the key.

- Merge
    - Used to combine two stream (kStream) into single KStream
    - KStream1::Topic1  and KStream2::Topic2
    - Channel data from these two topics into single topic

    `var mergedStream = stream1.merge(stream2)`


- Serialization and Deserialization
    - `Serdes.String()`
    - Serdes is factory class in Kafka Streams that care of handling ser and des of key and value
    - `Consumed.with` and `Produce.with`


- Another way for serdes
    ```
    KStream<String, String> greetingStream = streamBuilder
            .stream(GREETINGS

    );  

    // In the application config
        
    Properties props = new Properties();
    props.put(StreamConfig.DEFAULT_KEY_SERDE_CLASS_CONFIG, Serdes.StringSerde.class);
    props.put(StreamConfig.DEFAULT_VALUE_SERDE_CLASS_CONFIG, Serdes.StringSerde.class);
    

    ```

- Custom Serdes
    ```
    Goal: 

    {
        "message": "Good Morning!",
        "timeStamp": "2024-..."
        
    }

    ```

    - Custom serdes -> We need ser and der
    - `record` in JDK 14 replace lombok way for creating getter and setter
    - Under Domain folder ```public record Greeting(String message, java.time.LocalDateTime timeStamp) {}
    
    ```
    public class GreetingSerializer implements Serializer<Greeting> {
        @Override
        public void configure(Map<String, ?> configs, boolean isKey) {
            Serializer.super.configure(configs, isKey);
        }

        @
    }

    ```


