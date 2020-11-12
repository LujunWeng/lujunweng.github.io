## EC2 Storage

### Common
1. Device naming could be changed over configuration and actual instance. 

### Amazon Elastic Block Store
1. It is durable, block-level storage volumes and recommended for database
2. Can one volume be attached to multiple instances?
    > An EBS volume can be attached to only one instance at a time, but multiple volumes can be attached to a single instance.


### Amazon EC2 Instance Store
1. Instance's own storage; it's temporary and data will be lost when instance stopped or terminated

### Amazon EFS File System
1. scalable file storage and needs be mounted.
2. can work as a common data source for multiple instances

### Amazon S3

### References
1. [Storage, User Guide](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/Storage.html)
2. [Device Naming](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/device_naming.html)