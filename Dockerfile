FROM  centos:centos7.2.1511

RUN echo "http_caching=none" >> /etc/yum.conf
RUN yum clean all

#
# Install additional repositories
#
RUN yum -y install epel-release
RUN yum -y install cmake3 git gcc gcc-c++ make zlib-devel
RUN git clone git@github.com:dectris/DectrisHdf5.git DectrisHdf5
RUN mkdir DectrisHdf5/build && cd DectrisHdf5/build && cmake3 .. && make -j4 && make install
RUN git clone https://github.com/google/googletest.git googletest
RUN mkdir googletest/build && cd googletest/build && cmake3 .. && make -j4 && make install



