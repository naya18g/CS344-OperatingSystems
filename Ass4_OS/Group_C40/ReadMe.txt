ZFS Setup:
> Start by mounting USB drive on the system
> For installing ZFS utilities : sudo apt install zfs-fuse
> To start ZFS daemon : /etc/init.d/zfs-fuse start
> To obtain USB Drive Path : sudo fdisk -l
> Create ZFS pool on the USB Drive using : sudo zpool create <zpool_name> <Drive_path>
	we used zpool name as grc40 and our drive path was /dev/sdb

> To see the created pool use : sudo zpool list
> For enabling/disabling deduplication feature : 
sudo zfs set dedup=on <zpool_name> // for enabling dedup
sudo zfs set dedup=off <zpool_name> // for disabling dedup

> For enabling/disabling compression feature : 
sudo zfs set compression=on <zpool_name> // for enabling compression
sudo zfs set compression=off <zpool_name> // for disabling compression



ext3 Setup:
> Install mk2fs if not already installed : sudo apt-get install e2fsprogs
> To obtain USB Drive Path : sudo fdisk -l
> Create a mount point : mkdir /<mt_pt_name>
our name was ext_grc40
> Edit the /etc/fstab : sudo gedit /etc/fstab
add the following line to the file
 /dev/sdbc /ext_gr12 ext3 defaults 1 2
> To see directory details : df /<mt_pt_name>

