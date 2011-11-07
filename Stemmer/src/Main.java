import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Main {

	public static void main(String[] args) {

		WordNetStemmer wordNetStemmer = new WordNetStemmer();
		BufferedReader br;
		try {
			br = new BufferedReader(new FileReader(args[0]));
			PrintWriter out = new PrintWriter(new BufferedWriter(
					new FileWriter(args[1])));
			String line;
			while ((line = br.readLine()) != null) {
				out.println(line);
				if ((line = br.readLine()) != null) {
					String wordTab[] = line.split("\\s");
					for (String word : wordTab) {
						out.print(wordNetStemmer.Stem(word.toLowerCase()).toUpperCase() + " ");
					}
					out.println();
				}
			}
			br.close();
			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
