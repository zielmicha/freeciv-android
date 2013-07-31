// http://stackoverflow.com/questions/10633595/java-zip-how-to-unzip-folder
package com.zielm.p4a;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class ZipUtils
{
    private static final int BUFFER_SIZE = 4096;

    private static void extractFile(ZipInputStream in, File outdir, String name) throws IOException
    {
        byte[] buffer = new byte[BUFFER_SIZE];
        BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(new File(outdir,name)));
        int count = -1;
        while ((count = in.read(buffer)) != -1)
            out.write(buffer, 0, count);
        out.close();
    }

    private static void mkdirs(File outdir,String path)
    {
        File d = new File(outdir, path);
        if( !d.exists() )
            d.mkdirs();
    }

    private static String dirpart(String name)
    {
        int s = name.lastIndexOf( File.separatorChar );
        return s == -1 ? null : name.substring( 0, s );
    }

    /***
     * Extract zipfile to outdir with complete directory structure
     * @param zipfile Input .zip file
     * @param outdir Output directory
     */
    public static void extract(InputStream zipfile, File outdir)
    {
        try {
            ZipInputStream zin = new ZipInputStream(zipfile);
            ZipEntry entry;
            String name, dir;
            while ((entry = zin.getNextEntry()) != null) {
                name = entry.getName();
                if( entry.isDirectory() ) {
                    mkdirs(outdir,name);
                    continue;
                }
                /* this part is necessary because file entry can come before
                 * directory entry where is file located
                 * i.e.:
                 *   /foo/foo.txt
                 *   /foo/
                 */
                dir = dirpart(name);
                if( dir != null )
                    mkdirs(outdir,dir);

                extractFile(zin, outdir, name);
            }
            zin.close();
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
