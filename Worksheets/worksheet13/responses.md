# Worksheet 13

Diego Cruz and Saim Sheikh

## Given instructions:

Run the following commands to copy the APUE directory that you uncompressed in a previous worksheet:

```cmd
rsync -arv filedir/ filedir1/
cp -r filedir/ filedir2/
```

Now check the contents of each directory using the following commands:

```cmd
ls -latr filedir1/
ls -latr filedir2/
```

## What difference do you observe between the two directories?

Between the two directories, the one made with the `rsync` command directly copies the contents of the APUE folder, including the .3e folder. The directory copied using the `cp` command copies the actual APUE folder, and then the contents contained in said folder.